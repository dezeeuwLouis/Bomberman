/*
** move.c for bomberman in /root/Bureau/ETNA/bomberman/ovre_j/bomberman_server
**
** Made by OVRE Jordan
** Login   <ovre_j@etna-alternance.net>
**
** Started on  Wed Sep  7 23:06:15 2016 OVRE Jordan
** Last update Thu Sep  8 00:40:09 2016 OVRE Jordan
*/
#include "proto.h"

void Left(T_CLIENT* p_socket_client, T_DATA_MAP* data_map)
{
  if (p_socket_client->coordonnees.x > 0)
    {
      if (data_map->map[p_socket_client->coordonnees.y]
	  [p_socket_client->coordonnees.x - 1] == 'v')
	{
	  p_socket_client->last_coordonnees.x = p_socket_client->coordonnees.x;
	  p_socket_client->last_coordonnees.y = p_socket_client->coordonnees.y;
	  if (data_map->map[p_socket_client->last_coordonnees.y]
	      [p_socket_client->last_coordonnees.x] != 'b')
	    data_map->map[p_socket_client->last_coordonnees.y]
	      [p_socket_client->last_coordonnees.x] = 'v';
	  else
	    data_map->map[p_socket_client->last_coordonnees.y]
	      [p_socket_client->last_coordonnees.x] = 'b';
	  data_map->map[p_socket_client->coordonnees.y]
	    [p_socket_client->coordonnees.x - 1] = p_socket_client->nom;
	  p_socket_client->coordonnees.x -= 1;
	}
      else if (data_map->map[p_socket_client->coordonnees.y]
	       [p_socket_client->coordonnees.x - 1] == 'x')
        {
          p_socket_client->pv = 0;
          data_map->map[p_socket_client->last_coordonnees.y]
	    [p_socket_client->last_coordonnees.x] = 'v';
        }
    }
}

void Right(T_CLIENT* p_socket_client, T_DATA_MAP* data_map)
{
  if (p_socket_client->coordonnees.x < 15)
    {
      if (data_map->map[p_socket_client->coordonnees.y]
	  [p_socket_client->coordonnees.x + 1] == 'v')
	{
	  p_socket_client->last_coordonnees.x = p_socket_client->coordonnees.x;
	  p_socket_client->last_coordonnees.y = p_socket_client->coordonnees.y;
	  if (data_map->map[p_socket_client->last_coordonnees.y]
	      [p_socket_client->last_coordonnees.x] != 'b')
	    data_map->map[p_socket_client->last_coordonnees.y]
	      [p_socket_client->last_coordonnees.x] = 'v';
	  else
	    data_map->map[p_socket_client->last_coordonnees.y]
	      [p_socket_client->last_coordonnees.x] = 'b';
	  data_map->map[p_socket_client->coordonnees.y]
	    [p_socket_client->coordonnees.x + 1] = p_socket_client->nom;
	  p_socket_client->coordonnees.x += 1;
	}
      else if (data_map->map[p_socket_client->coordonnees.y]
	       [p_socket_client->coordonnees.x + 1] == 'x')
        {
          p_socket_client->pv = 0;
          data_map->map[p_socket_client->last_coordonnees.y]
	    [p_socket_client->last_coordonnees.x] = 'v';
        }
    }
}

void Down(T_CLIENT* p_socket_client, T_DATA_MAP* data_map)
{
  if (p_socket_client->coordonnees.y < 11)
    {
      if (data_map->map[p_socket_client->coordonnees.y + 1]
	  [p_socket_client->coordonnees.x] == 'v')
	{
	  p_socket_client->last_coordonnees.x = p_socket_client->coordonnees.x;
	  p_socket_client->last_coordonnees.y = p_socket_client->coordonnees.y;
	  if (data_map->map[p_socket_client->last_coordonnees.y]
	      [p_socket_client->last_coordonnees.x] != 'b')
	    data_map->map[p_socket_client->last_coordonnees.y]
	      [p_socket_client->last_coordonnees.x] = 'v';
	  else
	    data_map->map[p_socket_client->last_coordonnees.y]
	      [p_socket_client->last_coordonnees.x] = 'b';
	  data_map->map[p_socket_client->coordonnees.y + 1]
	    [p_socket_client->coordonnees.x] = p_socket_client->nom;
	  p_socket_client->coordonnees.y += 1;
	}
      else if (data_map->map[p_socket_client->coordonnees.y + 1]
	       [p_socket_client->coordonnees.x] == 'x')
        {
          p_socket_client->pv = 0;
          data_map->map[p_socket_client->last_coordonnees.y]
	    [p_socket_client->last_coordonnees.x] = 'v';
        }
    }
}

void Up(T_CLIENT* p_socket_client, T_DATA_MAP* data_map)
{
  if (p_socket_client->coordonnees.y > 0)
    {
      if (data_map->map[p_socket_client->coordonnees.y - 1]
	  [p_socket_client->coordonnees.x] == 'v')
	{
	  p_socket_client->last_coordonnees.x = p_socket_client->coordonnees.x;
	  p_socket_client->last_coordonnees.y = p_socket_client->coordonnees.y;
	  if (data_map->map[p_socket_client->last_coordonnees.y]
	      [p_socket_client->last_coordonnees.x] != 'b')
	    data_map->map[p_socket_client->last_coordonnees.y]
	      [p_socket_client->last_coordonnees.x] = 'v';
	  else
	    data_map->map[p_socket_client->last_coordonnees.y]
	      [p_socket_client->last_coordonnees.x] = 'b';
	  data_map->map[p_socket_client->coordonnees.y - 1]
	    [p_socket_client->coordonnees.x] = p_socket_client->nom;
	  p_socket_client->coordonnees.y -= 1;
	}
      else if (data_map->map[p_socket_client->coordonnees.y - 1]
	       [p_socket_client->coordonnees.x] == 'x')
	{
	  p_socket_client->pv = 0;
	  data_map->map[p_socket_client->last_coordonnees.y]
	    [p_socket_client->last_coordonnees.x] = 'v';
	}
    }
}
