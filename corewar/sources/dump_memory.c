/*
** dump_memory.c for dump_memory in /home/danilo_d/semestre2/no_message
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Fri Apr 10 17:04:57 2015 danilov dimitri
** Last update Sun Apr 12 12:20:18 2015 Bocquet Celestin
*/

#include	"cw.h"

int		my_putnbr_base(unsigned char nb, char *base)
{
  int		result;
  int		diviseur;
  int		size;

  size = my_strlen(base);
  diviseur = 1;
  while ((nb / diviseur) >= size)
    diviseur = diviseur * size;
  while (diviseur > 0)
    {
      result = (nb / diviseur) % size;
      my_putchar(base[result]);
      diviseur = diviseur / size;
    }
  return (0);
}

int		dump_memory(t_corewar *corewar)
{
  int		i;
  int		j;

  i = -1;
  j = 0;
  while (++i != MEM_SIZE)
    {
      if (corewar->memory.mem[i] < 16)
	my_putchar('0');
      my_putnbr_base(corewar->memory.mem[i], "0123456789ABCDEF");
      my_putchar(' ');
      j++;
      if (j >= 32)
	{
	  j = 0;
	  my_putchar('\n');
	}
    }
  return (0);
}
