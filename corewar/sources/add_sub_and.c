/*
** add_sub_and.c for add_subb_and in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Fri Apr  3 17:03:54 2015 danilov dimitri
** Last update Sun Apr 12 13:59:55 2015 danilov dimitri
*/

#include	"cw.h"

int		add(t_corewar *core_ware, t_champ *champ)
{
  int		i;

  if (champ->wait_cycle == 0)
    champ->wait_cycle = 10;
  else if (champ->wait_cycle > 1)
    champ->wait_cycle--;
  else if (champ->wait_cycle == 1)
    {
      (void)core_ware;
      i = 0;
      while (++i != 4)
	{
	  if (champ->instruction.instruction[i] >= REG_NUMBER
	      || champ->instruction.instruction[i] <= 0)
	    return (0);
	}
      champ->wait_cycle = 0;
      champ->carry = 1;
      champ->registre[champ->instruction.instruction[3]] =
	champ->registre[champ->instruction.instruction[1]] +
	champ->registre[champ->instruction.instruction[2]];
      clean_instruction(champ);
    }
  return (0);
}

int		sub(t_corewar *core_ware, t_champ *champ)
{
  int		i;

  if (champ->wait_cycle == 0)
    champ->wait_cycle = 10;
  else if (champ->wait_cycle > 1)
    champ->wait_cycle--;
  else if (champ->wait_cycle == 1)
    {
      (void)core_ware;
      champ->wait_cycle = 0;
      i = 0;
      while (++i != 4)
	{
	  if (champ->instruction.instruction[i] > REG_NUMBER
	      || champ->instruction.instruction[i] < 0)
	    return (0);
	}
      champ->registre[champ->instruction.instruction[3]] =
	champ->registre[champ->instruction.instruction[1]] -
	champ->registre[champ->instruction.instruction[2]];
      clean_instruction(champ);
    }
  return (0);
}

int		and(t_corewar *core_ware, t_champ *champ)
{
  if (champ->wait_cycle == 0)
    champ->wait_cycle = 6;
  else if (champ->wait_cycle > 1)
    champ->wait_cycle--;
  else if (champ->wait_cycle == 1)
    {
      (void)core_ware;
      champ->wait_cycle = 0;
      champ->carry = 1;
      correct_instruction(champ);
      if (champ->instruction.instruction[3] > REG_NUMBER
	  || champ->instruction.instruction[3] <= 0)
	return (0);
      champ->registre[champ->instruction.instruction[3]] =
	champ->instruction.instruction[1] &
	champ->instruction.instruction[2];
      clean_instruction(champ);
    }
  return (0);
}
