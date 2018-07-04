/*
** check_arg.c for check_arg in /root/Desktop/projetlib/ovre_j/libParse
**
** Made by OVRE Jordan
** Login   <ovre_j@etna-alternance.net>
**
** Started on  Tue Apr 28 22:34:35 2015 OVRE Jordan
** Last update Tue Apr 28 23:42:30 2015 OVRE Jordan
*/
#include "proto.h"

int check_doubles(char* format, int i, char* val_to_cmp, int cpt)
{
  char* arg;

  arg = malloc(2* sizeof(char));
  if (arg == 0)
    return (0);
  arg =  strncpy(arg, format + i, 2);
  if (strcmp(val_to_cmp,arg) == 0)
    cpt++;
  free(arg);

  return (cpt);
}

//check si argument en double
int doubles(char* val_to_cmp, char* format_origin)
{
  int compteur;
  int i;
  int taille;

  compteur = 0;
  taille = strlen(format_origin);
  i = 0;
  while (i < taille)
    {
      if (format_origin[i] == ':')
	       i++;
      else
      	{
      	  check_doubles(format_origin, i, val_to_cmp, compteur);
      	  i += 2;
      	}
    }
  if (compteur == 0)
    return 1;

  return 0;
}

//verif si option lors appel de fct exist dans le format
int exist_opt(char* format, char** argv, int i)
{
  int cpt;
  int tmp;

  cpt = 0;
  tmp = 0;
  while ((unsigned)tmp < strlen(format))
    {
      if (format[tmp] == '-' && format[tmp + 1] == argv[i][1])
	       cpt++;
      tmp++;
    }
  if (cpt == 0)
    {
      printf("option %s inexistante dans le format indique!!\n", argv[i]);
      return (1);
    }
  return (0);
}

//verif des option lors appel de fonction
int verif_arg(char* format, int argc, char** argv)
{
  int i;
  int j;
  int flag;

  j = 0;
  while ((unsigned)j < strlen(format))
    {
      for (i = 1; i < argc; i++)
      	{
      	  if (argv[i][0] == '-' && !argv[i][1])
      	    {
      	      printf("Erreur aucune option indique derriere un '-'\n");
      	      return (1);
      	    }
      	  else if (argv[i][0] == '-' && argv[i][1])
      	    {
      	      flag = exist_opt(format, argv, i);
      	      if (flag != 0)
      		return (1);
      	    }
      	}
      j++;
    }
  return (0);
}
