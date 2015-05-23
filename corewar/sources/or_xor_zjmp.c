/*
**or_xor_zjmp.c for or_xor_zjmp in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Fri Apr  3 17:04:57 2015 danilov dimitri
** Last update Sun Apr 12 12:36:20 2015 Bocquet Celestin
*/

#include	"cw.h"

int		or(t_corewar *core_ware, t_champ *champ)
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
      if (check_registre(champ->instruction.instruction[3], 3) != 0)
	return (0);
      champ->registre[champ->instruction.instruction[3]] =
	champ->instruction.instruction[1] |
	champ->instruction.instruction[2];
    }
  return (0);
}

int		xor(t_corewar *core_ware, t_champ *champ)
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
      if (correct_instruction(champ) == -1
	  || (champ->instruction.instruction[3] >= REG_NUMBER ||
	      champ->instruction.instruction[3] <= 0))
	return (0);
      champ->registre[champ->instruction.instruction[3]] =
	champ->instruction.instruction[1] ^
	champ->instruction.instruction[2];
    }
  return (0);
}

int		zjmp(t_corewar *core_ware, t_champ *champ)
{
  if (champ->wait_cycle == 0)
    champ->wait_cycle = 20;
  else if (champ->wait_cycle > 1)
    champ->wait_cycle--;
  else if (champ->wait_cycle == 1)
    {
      (void)core_ware;
      champ->pc = champ->pc + (champ->instruction.instruction[1] % IDX_MOD);
      champ->pc -= 4;
      champ->wait_cycle = 0;
    }
  return (0);
}
