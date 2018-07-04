/*
** initdata.c for bomberman in /root/Bureau/ETNA/bomberman/ovre_j/bomberman_server
**
** Made by OVRE Jordan
** Login   <ovre_j@etna-alternance.net>
**
** Started on  Wed Sep  7 23:06:32 2016 OVRE Jordan
** Last update Wed Sep  7 23:06:38 2016 OVRE Jordan
*/
#include "proto.h"

void init_orientation(T_CLIENT* l_all_clients, int x, int y, T_DATA_MAP data_map, opt_s* option)
{
  int i;
  T_INFOS_CONNEXION l_infos_connexion;
  list_s *bomb;

  bomb = NULL;
  l_all_clients[0].nom = '1';
  l_all_clients[1].nom = '2';
  l_all_clients[2].nom = '3';
  l_all_clients[3].nom = '4';
  for (i = 0; i < 4; i++)
    {
      l_all_clients[i].client_socket = 0;
      l_all_clients[i].pv = 1;
      l_all_clients[i].coordonnees = initialiseCoordonnes(i, x, y);
      l_all_clients[i].last_coordonnees = l_all_clients[i].coordonnees;
      l_all_clients[i].l_donnees_map = &data_map;
      l_all_clients[i].queue_bomb = bomb;
      l_all_clients[i].nb_bombe = 1;
      l_all_clients[i].flagdead = 0;
    }
  l_infos_connexion = initConnexionTcp(option);
  launchGame(l_infos_connexion, l_all_clients, 0, data_map);
}
