/*
** liste.c for bomberman in /root/Bureau/ETNA/bomberman/ovre_j/bomberman_server
** 
** Made by OVRE Jordan
** Login   <ovre_j@etna-alternance.net>
** 
** Started on  Wed Sep  7 23:03:46 2016 OVRE Jordan
** Last update Thu Sep  8 00:41:46 2016 OVRE Jordan
*/
#include "proto.h"

list_s* createList(int coord1, int coord2)
{
  list_s *news;

  news = malloc(sizeof(list_s));
  if (news)
    {
      news->x = coord1;
      news->y = coord2;
      news->state = 'd';
      return (news);
    }
  else
    return (0);
}

list_s* addEnd(list_s* listchain, int coord1, int coord2)
{
  list_s* news;
  list_s* tmp;

  news = malloc(sizeof(list_s));
  if (news == NULL)
    return (0);
  tmp = listchain;
  news->x = coord1;
  news->y = coord2;
  news->state = 'd';
  news->nxt = NULL;
  if (listchain == NULL)
    return (news);
  else
    {
      while (tmp->nxt != NULL)
	tmp = tmp->nxt;
      tmp->nxt = news;
      return (listchain);
    }
}

list_s* findElmt(list_s* p_list, char p_index)
{
  if(p_list == NULL)
    return (NULL);
  while (p_list->state != p_index && p_list != NULL)
    p_list = p_list->nxt;
  if(p_list == NULL)
    return (NULL);
  else
    return (p_list);
}

list_s* delList(list_s* listchain)
{
  list_s* tmp;
  list_s* nxt;

  tmp = listchain;
  nxt = NULL;
  while (tmp != NULL)
    {
      nxt = tmp->nxt;
      free(tmp);
      tmp = nxt;
    }
  return (0);
}

list_s* rmElmt(list_s* listchain, int coord1, int coord2)
{
  list_s* tmp;
  list_s* prev;

  if (listchain == NULL)
    return (listchain);
  prev = listchain;
  if (prev->x == coord1 && prev->y == coord2)
    {
      listchain = prev->nxt;
      free(prev);
      return (listchain);
    }
  tmp = prev->nxt;
  while (tmp != NULL)
    {
      if (tmp->x == coord1 && tmp->y == coord2)
    	{
    	  prev->nxt = tmp->nxt;
    	  free(tmp);
    	  return listchain;
    	}
      prev = tmp;
      tmp = tmp->nxt;
    }
  return listchain;
}

list_s* delList2(list_s* listchain)
{
  list_s* tmp;
  list_s* nxt;

  tmp = listchain;
  nxt = NULL;
  while (tmp != NULL)
    {
      nxt = tmp->nxt;
      free(tmp);
      tmp = nxt;
    }
  return (0);
}
