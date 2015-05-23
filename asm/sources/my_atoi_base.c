/*
** my_atoi_base.c for corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar/asm
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Wed Apr  8 18:48:33 2015 Boulay Arnaud
** Last update Thu Apr  9 11:58:02 2015 Boulay Arnaud
*/

#include <stdlib.h>
#include "asm.h"

int     getnb(char nb, char *base)
{
  int   i;

  i = -1;
  while (base[++i] != '\0')
    if (nb == base[i])
      return (i);
  return (0);
}

int	my_atoi_base(char *str, char *base)
{
  int	neg;
  int   basenb;
  int	rslt;
  int	div;
  int	i;

  i = 0;
  div = 1;
  rslt = 0;
  basenb = my_strlen(base);
  neg = (str[0] == '-') ? 1 : 0;
  while (str[++i] != '\0')
    if (is_inside(base, str[i]) == 1)
      div = div * basenb;
    else
      return (-1);
  i = -1;
  while (div > 0 && str[++i] != '\0')
    {
      rslt = rslt + getnb(str[i], base) * div;
      div = div / basenb;
    }
  rslt = (neg == 1) ? rslt * -1 : rslt;
  return (rslt);
}
