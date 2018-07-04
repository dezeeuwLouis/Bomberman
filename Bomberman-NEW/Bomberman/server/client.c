/*
** client.c for bomberman in /root/Bureau/ETNA/bomberman/ovre_j/bomberman_server
**
** Made by OVRE Jordan
** Login   <ovre_j@etna-alternance.net>
**
** Started on  Wed Sep  7 23:05:28 2016 OVRE Jordan
** Last update Thu Sep  8 00:38:57 2016 OVRE Jordan
*/
#include "proto.h"

void messageReceivedFromClient(T_CLIENT* l_all_clients,T_INFOS_CONNEXION*
			       p_infos_connexion, T_DATA_MAP* data_map)
{
  int i;
  int sd;
  char buffer[2];
  int valread;

  valread = 0;
  sd = 0;
  for (i = 0; i < 4; i++)
    {
      sd = l_all_clients[i].client_socket;
      if (FD_ISSET(sd , &p_infos_connexion->readfds))
	{
          valread = recv(sd, buffer , 2, 0);
          if (valread == 0 && p_infos_connexion->l_etat_partie != 1)
      	    {
	      close(sd);
	      l_all_clients[i].client_socket = 0;
	      NOMBRE_JOUEUR--;
	      my_putstr("1 joueur s'est déconnecté.\n");
      	    }
          else if (p_infos_connexion->l_etat_partie == 1)
	    {
	      gestionCommandeRecu(buffer, valread, l_all_clients, i, data_map);
	    }
	}
    }
}

int waitingClientConnexion(T_INFOS_CONNEXION p_infos_connexion,
			   T_CLIENT* l_all_clients)
{
  int new_socket;
  int i;

  i = 0;
  new_socket = 0;
  if (FD_ISSET(p_infos_connexion.master_socket, &p_infos_connexion.readfds)
      && p_infos_connexion.l_etat_partie == 0)
    {
      if ((new_socket = accept(p_infos_connexion.master_socket,
			       (struct sockaddr *)&p_infos_connexion.address,
			       (socklen_t*)&p_infos_connexion.addrlen))<0)
	perror("accept");
      for (i = 0; i < 4; i++)
	{
	  if( l_all_clients[i].client_socket == 0)
	    {
	      l_all_clients[i].client_socket = new_socket;
	      i = 4;
	    }
	}
      my_putstr("1 joueur s'est connecté.\n");
      return (1);
    }
  return (0);
}
