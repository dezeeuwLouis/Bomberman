/*
** delliste.c for bomberman in /root/Bureau/ETNA/bomberman/ovre_j/bomberman_server
** 
** Made by OVRE Jordan
** Login   <ovre_j@etna-alternance.net>
** 
** Started on  Wed Sep  7 23:05:59 2016 OVRE Jordan
** Last update Wed Sep  7 23:06:02 2016 OVRE Jordan
*/
#include "proto.h"

opt_s* delListe(opt_s* liste)
{
  opt_s* tmp;
  opt_s* nxt;

  tmp = liste;
  nxt = NULL;
  while(tmp != NULL)
    {
      nxt = tmp->nxt;
      free(tmp);
      tmp = nxt;
    }
  return (0);
}
