/*
** other.c for bomberman in /root/Bureau/ETNA/bomberman/ovre_j/bomberman_server
** 
** Made by OVRE Jordan
** Login   <ovre_j@etna-alternance.net>
** 
** Started on  Wed Sep  7 23:04:52 2016 OVRE Jordan
** Last update Wed Sep  7 23:04:54 2016 OVRE Jordan
*/
#include "proto.h"

int my_tablen(char tab[])
{
  int i;
  int cpt;

  i = 0;
  cpt = 0;
  while (tab[i] != '\0')
    {
      i++;
      cpt++;
    }
  return (cpt);
}

int my_putstr(char *str)
{
  int i;
  int cpt;

  if (!str)
    {
      my_putchar('(');
      my_putchar('n');
      my_putchar('u');
      my_putchar('l');
      my_putchar('l');
      my_putchar(')');
      return (1);
    }
  cpt = my_tablen(str);
  for (i = 0; i < cpt; i++)
    {
      my_putchar(str[i]);
    }
  return (0);
}

void my_putchar(char c)
{
  write (1, &c, 1);
}
