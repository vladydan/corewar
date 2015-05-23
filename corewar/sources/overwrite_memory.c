/*
** overwrite_memory.c for overtwrite_memory in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Mon Apr  6 11:13:04 2015 danilov dimitri
** Last update Sun Apr 12 16:20:17 2015 danilov dimitri
*/

#include	"cw.h"

int		find_index(t_corewar *corewar, unsigned char *address)
{
  int		index;

  index = address - corewar->memory.begin_memory;
  return (index);
}

unsigned char	*check_if_overide(t_corewar *corewar, unsigned char *address)
{
  int		tmp;

  if (address > corewar->memory.begin_memory
      && address < corewar->memory.end_memory)
    return (address);
  else if (address > corewar->memory.end_memory)
    {
      tmp = address - corewar->memory.end_memory;
      while (tmp > MEM_SIZE)
	tmp -= MEM_SIZE;
      return (corewar->memory.begin_memory + tmp);
    }
  else if (address < corewar->memory.begin_memory)
    {
      return (corewar->memory.begin_memory);
    }
  return (address);
}

int		overwrite_four_bytes(unsigned char *adress, t_champ *champ,
				     t_corewar *corewar)
{
  t_union	uni;
  int		i;
  int		index;

  adress = check_if_overide(corewar, adress);
  i = 4;
  if (check_registre(champ->instruction.instruction[1], 2) != 0)
    return (0);
  uni.nbr = champ->registre[champ->instruction.instruction[1]];
  while (--i != - 1)
    {
      index = find_index(corewar, adress);
      if (index < 0 || index > MEM_SIZE)
	return (0);
      corewar->memory.own_mem[index] = champ->nbr_champ;
      *adress = uni.byte[i];
      adress++;
      adress = check_if_overide(corewar, adress);
    }
  aff_memory(corewar);
  return (0);
}

int		overwrite_four_bytes_st(unsigned char *adress, int nbr,
					t_champ *champ, t_corewar *corewar)
{
  t_union	uni;
  int		i;
  int		index;

  adress = check_if_overide(corewar, adress);
  i = 4;
  uni.nbr = nbr;
  while (--i != - 1)
    {
      index = find_index(corewar, adress);
      if (index < 0 || index > MEM_SIZE)
	return (0);
      corewar->memory.own_mem[index] = champ->nbr_champ;
      *adress = uni.byte[i];
      adress++;
      adress = check_if_overide(corewar, adress);
    }
  aff_memory(corewar);
  return (0);
}

int		get_four_bytes(unsigned char *address)
{
  t_union	uni;
  int		i;

  i = 4;
  while (--i != -1)
    {
      uni.byte[i] = *address;
      address = address + 1;
    }
  return (uni.nbr);
}
