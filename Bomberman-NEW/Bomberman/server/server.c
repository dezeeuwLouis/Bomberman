/*
** server.c for bomberman in /root/Bureau/ETNA/bomberman/ovre_j/bomberman_server
**
** Made by OVRE Jordan
** Login   <ovre_j@etna-alternance.net>
**
** Started on  Wed Sep  7 23:05:14 2016 OVRE Jordan
** Last update Thu Sep  8 00:42:33 2016 OVRE Jordan
*/
#include "proto.h"

int ETAT_PARTIE = 1;
int NOMBRE_JOUEUR = 0;

void IsDie(T_CLIENT* p_socket_client)
{
  int retour;

  my_putstr("nb joueur = ");
  my_put_nbr(NOMBRE_JOUEUR);
  my_putchar('\n');
  if (p_socket_client->pv <= 0)
    {
      retour = send(p_socket_client->client_socket, "d", 1, 0);
      if(retour != 1 )
	perror("send");
      if (p_socket_client->flagdead != 1)
	if (NOMBRE_JOUEUR > 1)
	  NOMBRE_JOUEUR -= 1;
      p_socket_client->flagdead = 1;
    }
  else
    {
      retour = send(p_socket_client->client_socket, "0", 1, 0);
      if(retour != 1 )
	perror("send");
    }
  if (NOMBRE_JOUEUR == 1)
    ETAT_PARTIE = 42;
}

void gestionCommandeRecu(char* p_buffer, int p_taille_buffer,
			 T_CLIENT* p_socket_client, int index_client_recu, T_DATA_MAP* data_map)
{
  p_buffer[p_taille_buffer] = '\0';
  if (p_buffer[0] == 'u')
    SendMap(p_socket_client, index_client_recu, data_map);
  else if (p_buffer[0] == '1')
    Up(&p_socket_client[index_client_recu], data_map);
  else if (p_buffer[0] == '2')
    Down(&p_socket_client[index_client_recu], data_map);
  else if (p_buffer[0] == '3')
    Left(&p_socket_client[index_client_recu], data_map);
  else if (p_buffer[0] == '4')
    Right(&p_socket_client[index_client_recu], data_map);
  else if (p_buffer[0] == '5')
    BombDrop(&p_socket_client[index_client_recu], data_map);
  else if (p_buffer[0] == '6')
    ExplosionBombe(p_socket_client, &p_socket_client[index_client_recu],
		   data_map);
  else if (p_buffer[0] == '7')
    FinExplosion(&p_socket_client[index_client_recu], data_map);
  else if (p_buffer[0] == 's')
    IsDie(&p_socket_client[index_client_recu]);
}

void launchGame(T_INFOS_CONNEXION l_infos_connexion, T_CLIENT* l_all_clients,
		int i, T_DATA_MAP data_map)
{
  int sd;
  int max_sd;
  int activity;
  char win;
  int l_flag_while;
  struct timeval tv;

  l_flag_while = 1;
  l_infos_connexion.l_etat_partie = 0;
  max_sd = 0;
  sd = 0;
  activity = 0;
  tv.tv_sec = TIMEOUT_SEC;
  tv.tv_usec = TIMEOUT_USEC;
  while(l_flag_while == 1)
    {
      FD_ZERO(&l_infos_connexion.readfds);
      FD_SET(l_infos_connexion.master_socket, &l_infos_connexion.readfds);
      max_sd = l_infos_connexion.master_socket;
      for ( i = 0 ; i < 4 ; i++)
        {
          sd = l_all_clients[i].client_socket;
          if(sd > 0)
            FD_SET(sd , &l_infos_connexion.readfds);
          if(sd > max_sd)
            max_sd = sd;
        }
      activity = select(max_sd + 1, &l_infos_connexion.readfds, NULL, NULL, &tv);
      if(activity < 0)
      	{
      	  perror("select");
      	  return;
      	}
      if (activity > 0)
        {
      	  NOMBRE_JOUEUR += waitingClientConnexion(l_infos_connexion, l_all_clients);
      	  messageReceivedFromClient(l_all_clients, &l_infos_connexion, &data_map);
        }
      if (NOMBRE_JOUEUR == 4 && l_infos_connexion.l_etat_partie == 0)
        {
          my_putstr("Let's go !\n");
          l_infos_connexion.l_etat_partie = 1;
          for (i = 0; i < 4; i++)
            if(send(l_all_clients[i].client_socket, "0", 1, 0) != 1 )
              perror("send");
        }
      if (NOMBRE_JOUEUR == 1 && ETAT_PARTIE == 42)
        {
          my_putstr("Il ne reste qu'un joueur il a gagné ! \n");
          for (i = 0; i < 4; i++)
	    {
	      if (l_all_clients[i].pv > 0)
		win = l_all_clients[i].nom;
	    }
          for (i = 0; i < 4; i++)
	    {
	      if((send(l_all_clients[i].client_socket, "w", 1, 0)) != 1 )
		perror("send");
	      if((send(l_all_clients[i].client_socket, &win, 1, 0)) != 1 )
		perror("send");
	      l_all_clients[i].queue_bomb = delList2(l_all_clients[i].queue_bomb);
	    }
          l_flag_while = 0;
          ETAT_PARTIE = 0;
          sleep(3);
          close(l_all_clients[i].client_socket);
        }
      else if (ETAT_PARTIE == 0 && NOMBRE_JOUEUR == 0)
	l_flag_while = 0;
    }
}

T_INFOS_CONNEXION initConnexionTcp(opt_s* option)
{
  T_INFOS_CONNEXION l_infos_connexion;
  int opt;

  opt = TRUE;
  if((l_infos_connexion.master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    perror("socket failed");
  if( setsockopt(l_infos_connexion.master_socket, SOL_SOCKET, SO_REUSEADDR,
		 (char *)&opt, sizeof(opt)) < 0 )
    perror("setsockopt");
  l_infos_connexion.address.sin_family = AF_INET;
  l_infos_connexion.address.sin_addr.s_addr = INADDR_ANY;
  l_infos_connexion.address.sin_port = htons(addPort(option));
  if (bind(l_infos_connexion.master_socket, (struct sockaddr *)
	   &l_infos_connexion.address, sizeof(l_infos_connexion.address))<0)
    perror("bind failed");
  if (listen(l_infos_connexion.master_socket, 3) < 0)
    perror("listen");
  l_infos_connexion.addrlen = sizeof(l_infos_connexion.address);
  my_putstr("Waiting for connections ...\n");
  return (l_infos_connexion);
}

int main(int argc , char *argv[])
{
  T_CLIENT l_all_clients[4];
  int x;
  int y;
  T_DATA_MAP data_map;
  opt_s* option;

  option = ajoutArg(argc, argv);
  if (addPort(option) == -1)
    {
      delListe(option);
      return (-1);
    }
  x = 15;
  y = 11;
  data_map = initialisationMap(data_map, x, y);
  init_orientation(l_all_clients, x, y, data_map, option);
  delListe(option);
  freeMap(data_map);
  return (0);
}
