/*
** other2.c for bomberman in /root/Bureau/ETNA/bomberman/ovre_j/bomberman_server
** 
** Made by OVRE Jordan
** Login   <ovre_j@etna-alternance.net>
** 
** Started on  Wed Sep  7 23:04:35 2016 OVRE Jordan
** Last update Wed Sep  7 23:04:38 2016 OVRE Jordan
*/
#include "proto.h"

int my_nb_len(long n)
{
  int essai;

  essai = 0;
  if (n < 0)
    {
      n *= -1;
    }
  while (n >= 1)
    {
      essai++;
      n /= 10;
    }
  return (essai);
}

int my_neg(int n, int neg_max)
{
  if (n < 0)
    {
      if (neg_max == 1)
	n += 1;
      my_putchar(45);
      n *= -1;
    }
  return (n);
}

void my_put_nbr(int n)
{
  long ent;
  int len;
  int modulo;
  int neg_max;

  modulo = 1;
  len = my_nb_len(n);
  (n == -2147483648 ? (neg_max = 1) : (neg_max = 0));
  n = my_neg(n, neg_max);
  while (len > 1)
    {
      modulo *= 10;
      len--;
    }
  ent = ((n / modulo) + 48);
  my_putchar(ent);
  while (modulo >= 10)
    {
      ent = n % modulo;
      modulo /= 10;
      if (neg_max == 1 && modulo == 1)
	ent += 1;
      len = ((ent / modulo) + 48);
      my_putchar(len);
    }
}
