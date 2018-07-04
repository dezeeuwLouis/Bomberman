/*
** main.c for libParse in /root/Desktop/projetlib/ovre_j/libParse
**
** Made by OVRE Jordan
** Login   <ovre_j@etna-alternance.net>
**
** Started on  Sun Apr 26 21:53:17 2015 OVRE Jordan
** Last update Tue Apr 28 23:39:39 2015 OVRE Jordan
*/
#include "proto.h"

//si option ok ajout liste chainer
opt_s* addStartOpt(opt_s* option, char name, char* val, int flag)
{
  opt_s* news;

  news = malloc(sizeof(opt_s));
  if (news == 0)
    return (0);
  news->name = name;
  if (flag == 0)
    news->valeur = val;
  else
    news->valeur = NULL;
  news->nxt = option;
  return (news);
}

//fonction de verification de passage d'arg à l'option
opt_s* error_usage(char** argv, int i, opt_s* option, char* format)
{
  if (!argv[i + 1] || argv[i + 1][0] == '-')
    {
      printf("error usage for argument %s \n", argv[i]);
      return(option);
    }
  else if (doubles(argv[i+1], format) != 0)
    option = addStartOpt(option, argv[i][1], argv[i+1], 0);

  return (option);
}

// fct de verification des option lors appel de programme
opt_s* my_getopt(int argc, char** argv, char* format)
{
  int i;
  int j;
  opt_s* option;

  j = 0;
  option = NULL;
  i = verif_arg(format, argc, argv);
  if (i != 0)
    return (0);
  while ((unsigned)j < strlen(format))
    {
      for (i = 1; i < argc; i++)
	{
	  if (format[j] == '-' && format[j + 1] == argv[i][1])
	    {
	      j++;
	      if (format[j + 1] == ':')
		option = error_usage(argv, i, option, format);
	      else
		option = addStartOpt(option, argv[i][1], "0", 1);
	    }
	}
      j++;
    }
  return (option);
}
