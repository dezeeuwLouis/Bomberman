/*
** arg.c for bomberman in /root/Bureau/ETNA/bomberman/ovre_j/bomberman_server
** 
** Made by OVRE Jordan
** Login   <ovre_j@etna-alternance.net>
** 
** Started on  Wed Sep  7 23:03:13 2016 OVRE Jordan
** Last update Thu Sep  8 00:38:10 2016 OVRE Jordan
*/
#include "proto.h"

opt_s* ajoutArg(int argc, char** argv)
{
  opt_s* option;
  int i;

  for (i = 0; i < argc; i++)
    {
      if (strcmp("--port", argv[i]) == 0)
	argv[i] = "-p";
    }
  option = my_getopt(argc, argv, "-v-s:-l:-c:-p:");
  return (option);
}

int addPort(opt_s* option)
{
  opt_s* tmp;
  int PORT;
  int flag;

  tmp = option;
  flag = 0;
  while (tmp != NULL)
    {
      if (tmp->name == 'p')
      	{
      	  PORT = atoi(tmp->valeur);
      	  flag = 1;
      	}
      tmp = tmp->nxt;
    }
  if (flag == 1)
    return (PORT);
  else
    {
      my_putstr("Erreur, aucun port spécifié\n");
      return (-1);
    }
}
