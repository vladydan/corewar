/*
** tools.c for corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Wed Apr  8 11:53:26 2015 Boulay Arnaud
** Last update Sat Apr 11 19:59:54 2015 Boulay Arnaud
*/

#include <stdlib.h>
#include "asm.h"

void	set_buffer(char *buff, int size)
{
  int	i;

  i = -1;
  while (++i != size)
    buff[i] = '\0';
}

int	is_inside(char *str, char c)
{
  int	i;

  i = -1;
  while (str[++i] != '\0')
    if (str[i] == c)
      return (1);
  return (0);
}

int	my_tablen(char **tab)
{
  int	i;

  i = 0;
  while (tab[i] != NULL)
    ++i;
  return (i);
}

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    ++i;
  return (i);
}
