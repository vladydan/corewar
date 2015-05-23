/*
** my_calloc.c for my_calloc in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Mon Mar 30 14:43:27 2015 danilov dimitri
** Last update Sun Apr 12 21:59:58 2015 danilov dimitri
*/

#include	"cw.h"

int		reserve_memory(t_corewar *corewar)
{
  int		i;

  i = 0;
  if ((corewar->memory.mem = malloc(sizeof(unsigned char) * MEM_SIZE)) == NULL)
    return (-1);
  if ((corewar->memory.own_mem = malloc(sizeof(unsigned char)
					* MEM_SIZE)) == NULL)
    return (-1);
  corewar->memory.begin_memory = &corewar->memory.mem[0];
  while (i < MEM_SIZE)
    {
      corewar->memory.mem[i] = 0;
      ++i;
    }
  corewar->memory.end_memory = &corewar->memory.mem[--i];
  return (0);
}
