/*
** bombe.c for bomberman in /root/Bureau/ETNA/bomberman/ovre_j/bomberman_server
**
** Made by OVRE Jordan
** Login   <ovre_j@etna-alternance.net>
**
** Started on  Wed Sep  7 23:04:12 2016 OVRE Jordan
** Last update Thu Sep  8 00:41:10 2016 OVRE Jordan
*/
#include "proto.h"

void BombDrop(T_CLIENT* p_socket_client, T_DATA_MAP* data_map)
{
  int retour;

  if (p_socket_client->nb_bombe != 0 )
    {
      p_socket_client->last_coordonnees.x = p_socket_client->coordonnees.x;
      p_socket_client->last_coordonnees.y = p_socket_client->coordonnees.y;
      data_map->map[p_socket_client->last_coordonnees.y]
        [p_socket_client->last_coordonnees.x] = 'b';
      if (p_socket_client->queue_bomb == NULL)
	p_socket_client->queue_bomb = addEnd(p_socket_client->queue_bomb,
					     p_socket_client->coordonnees.x, p_socket_client->coordonnees.y);
      p_socket_client->nb_bombe -= 1;
      retour = send(p_socket_client->client_socket, "0", 1, 0);
      if(retour != 1 )
	perror("send");
    }
  else
    {
      retour = send(p_socket_client->client_socket, "1", 1, 0);
      if(retour != 1 )
	perror("send");
    }
}

void FinExplosion(T_CLIENT* p_socket_client, T_DATA_MAP* data_map)
{
  int i;
  list_s *bombe;

  bombe = findElmt(p_socket_client->queue_bomb, 'f');
  if (bombe != NULL)
    {
      /*data_map->map[bombe->y][bombe->x] = 'v';*/
      for (i = 0; i < 3; i++)
	{
	  if (bombe->x >= (0 + i))
	    if ((data_map->map[bombe->y][bombe->x - i]) == 'x')
	      data_map->map[bombe->y][bombe->x - i] = 'v';
	  if (bombe->x < (15 - i))
	    if ((data_map->map[bombe->y][bombe->x + i]) == 'x')
	      data_map->map[bombe->y][bombe->x + i] = 'v';
	  if (bombe->y >= (0 + i))
	    if ((data_map->map[bombe->y - i][bombe->x]) == 'x')
	      data_map->map[bombe->y - i][bombe->x] = 'v';
	  if (bombe->y < (11 - i))
	    if ((data_map->map[bombe->y + i][bombe->x]) == 'x')
	      data_map->map[bombe->y + i][bombe->x] = 'v';
	}
      p_socket_client->queue_bomb = rmElmt(p_socket_client->queue_bomb,
					   bombe->x, bombe->y);
      p_socket_client->nb_bombe += 1;
    }
}

void ExplosionBombe(T_CLIENT* all_socket_client, T_CLIENT* p_socket_client,
		    T_DATA_MAP* data_map)
{
  int i;
  list_s *bombe;

  bombe = findElmt(p_socket_client->queue_bomb, 'd');
  if (bombe != NULL)
    {
      bombe->state = 'f';
      data_map->map[bombe->y][bombe->x] = 'x';
      for (i = 0; (((bombe->x >= (0 + i)) &&
		    (data_map->map[bombe->y][bombe->x - i]) != 'm') && i < 3);i++)
	data_map->map[bombe->y][bombe->x - i] = 'x';
      for (i = 0; (((bombe->y >= (0 + i)) &&
		    (data_map->map[bombe->y - i][bombe->x]) != 'm') && i < 3);i++)
	data_map->map[bombe->y - i][bombe->x] = 'x';
      for (i = 0; (((bombe->x < (15 - i)) &&
		    (data_map->map[bombe->y][bombe->x + i]) != 'm') && i < 3);i++)
	data_map->map[bombe->y][bombe->x + i] = 'x';
      for (i = 0; (((bombe->y < (11 - i)) &&
		    (data_map->map[bombe->y + i][bombe->x]) != 'm') && i < 3);i++)
	data_map->map[bombe->y + i][bombe->x] = 'x';
    }
  for (i = 0; i < 4; i++)
    if (data_map->map[all_socket_client[i].coordonnees.y]
	[all_socket_client[i].coordonnees.x] ==  'x')
      all_socket_client[i].pv = 0;

}
