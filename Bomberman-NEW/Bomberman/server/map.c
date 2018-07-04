/*
** map.c for bomberman in /root/Bureau/ETNA/bomberman/ovre_j/bomberman_server
**
** Made by OVRE Jordan
** Login   <ovre_j@etna-alternance.net>
**
** Started on  Wed Sep  7 23:05:42 2016 OVRE Jordan
** Last update Thu Sep  8 00:41:59 2016 OVRE Jordan
*/
#include "proto.h"

T_DATA_MAP initialisationMap(T_DATA_MAP p_data_map, int x, int y)
{
  int i;
  int j;

  if (( p_data_map.map = (char**)malloc(y*sizeof( char* ))) == NULL )
    perror("error");
  for ( i = 0; i < x; i++ )
    if (( p_data_map.map[i] = (char*)malloc(x)) == NULL )
      perror("error");
  for (i = 0; i < y; i++)
    for (j = 0; j < x; j++)
      p_data_map.map[i][j] = 'v';
  p_data_map.map[0][7] = 'w';
  p_data_map.map[5][0] = 'w';
  p_data_map.map[10][7] = 'w';
  p_data_map.map[5][14] = 'w';
  return (initialisationMap2(p_data_map, x, y));
}

T_DATA_MAP initialisationMap2(T_DATA_MAP p_data_map, int x, int y)
{
  int i;
  int j;
  int flag;

  flag = 0;
  for (i = 1; i < y - 1; i++)
    for (j = 1; j < x - 1; j++)
      {
	if (i%2 != 0)
	  {
	    if (flag == 0)
	      {
		p_data_map.map[i][j] = 'm';
		flag = 1;
	      }
	    else if (flag == 1)
	      {
		p_data_map.map[i][j] = 'w';
		flag = 0;
	      }
	  }
	else
	  {
	    p_data_map.map[i][j] = 'w';
	    flag = 0;
	  }
      }
  return (initialisationMap3(p_data_map, x, y));
}

T_DATA_MAP initialisationMap3(T_DATA_MAP p_data_map, int x, int y)
{
  p_data_map.map[0][0] = '1';
  p_data_map.map[0][x-1] = '2';
  p_data_map.map[y-1][0] = '3';
  p_data_map.map[y-1][x-1] = '4';

  return (p_data_map);
}

void freeMap(T_DATA_MAP p_data_map)
{
  int i;

  for (i = 0; i < 15; i++)
    free(p_data_map.map[i]);
  free(p_data_map.map);
}

T_COORDONNES initialiseCoordonnes(int i, int x, int y)
{
  T_COORDONNES l_coordonnes;

  if (i == 0)
    {
      l_coordonnes.x = 0;
      l_coordonnes.y = 0;
    }
  if (i == 1)
    {
      l_coordonnes.x = 0;
      l_coordonnes.y = y - 1;
    }
  if (i == 2)
    {
      l_coordonnes.x = x - 1;
      l_coordonnes.y = 0;
    }
  if (i == 3)
    {
      l_coordonnes.x = x-1;
      l_coordonnes.y = y-1;
    }
  return (l_coordonnes);
}

void SendMap(T_CLIENT* p_socket_client, int index_client_recu,
	     T_DATA_MAP* data_map)
{
  int i;
  int retour;

  for (i = 0; i < 11; i++)
    {
      retour = send((&p_socket_client[index_client_recu])->client_socket,
		    data_map->map[i], strlen(data_map->map[i]), 0);
      if(retour != (int)strlen(data_map->map[i]))
        perror("send");
    }
}
