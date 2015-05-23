/*
** ldi_sti_lld_lldi.c for ldi_sti_lldi_lldi in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Fri Apr  3 17:06:08 2015 danilov dimitri
** Last update Sun Apr 12 17:05:22 2015 danilov dimitri
*/

#include	"cw.h"

int		ldi(t_corewar *corewar, t_champ *champ)
{
  int		nbr;
  unsigned char	*jump;

  if (champ->wait_cycle == 0)
    champ->wait_cycle = 25;
  else if (champ->wait_cycle > 1)
    champ->wait_cycle--;
  else if (champ->wait_cycle == 1)
    {
      correct_instruction(champ);
      nbr = champ->instruction.instruction[1] +
	champ->instruction.instruction[2];
      jump = champ->begin_instru + (nbr % IDX_MOD);
      jump = check_if_overide(corewar, jump);
      if (champ->instruction.instruction[3] > REG_NUMBER
	  || champ->instruction.instruction[3] <= 0)
	return (0);
      champ->registre[champ->instruction.instruction[3]] = get_four_bytes(jump);
      champ->wait_cycle = 0;
      clean_instruction(champ);
    }
  return (0);
}

int		sti(t_corewar *corewar, t_champ *champ)
{
  int		nbr;
  unsigned char	*jump;

  if (champ->wait_cycle == 0)
    champ->wait_cycle = 25;
  else if (champ->wait_cycle > 1)
    champ->wait_cycle--;
  else if (champ->wait_cycle == 1)
    {
      champ->wait_cycle = 0;
      if (champ->instruction.type_instr[1] == 1)
	if (check_registre(champ->instruction.instruction[2], 2 ) != 0)
	  return (0);
      if (champ->instruction.type_instr[2] == 1)
	if (check_registre(champ->instruction.instruction[3], 2 ) != 0)
	  return (0);
      nbr = add_two_parameter(champ);
      jump = champ->begin_instru + nbr;
      jump = check_if_overide(corewar, jump);
      overwrite_four_bytes(jump, champ, corewar);
      clean_instruction(champ);
    }
  return (0);
}

int		lld_2(t_corewar *core_ware, t_champ *champ)
{
  unsigned char *jmp;
  int		value;

  if (champ->instruction.type_instr[0] == 1)
    {
      if (check_registre(champ->instruction.instruction[1], 2) == -1)
	return (0);
      champ->registre[champ->instruction.instruction[2]] =
	champ->registre[champ->instruction.instruction[1]];
    }
  if (champ->instruction.type_instr[0] == 2)
    {
      jmp = champ->begin_instru + champ->instruction.instruction[1];
      jmp = check_if_overide(core_ware, jmp);
      value = get_four_bytes(jmp);
      champ->registre[champ->instruction.instruction[2]] = value;
    }
  if (champ->instruction.type_instr[0] == 4)
    {
      champ->registre[champ->instruction.instruction[2]] =
	champ->instruction.instruction[1];
    }
  return (0);
}

int		lld(t_corewar *core_ware, t_champ *champ)
{
  if (champ->wait_cycle == 0)
    champ->wait_cycle = 5;
  else if (champ->wait_cycle > 1)
    champ->wait_cycle--;
  else if (champ->wait_cycle == 1)
    {
      champ->wait_cycle = 0;
      if (check_registre(champ->instruction.instruction[2], 2) == -1)
	return (0);
      lld_2(core_ware, champ);
      clean_instruction(champ);
    }
  return (0);
}

int		lldi(t_corewar *corewar, t_champ *champ)
{
  unsigned char	*jump;
  int		nbr;

  if (champ->wait_cycle == 0)
    champ->wait_cycle = 50;
  else if (champ->wait_cycle > 1)
    champ->wait_cycle--;
  else if (champ->wait_cycle == 1)
    {
      correct_instruction(champ);
      nbr = champ->instruction.instruction[1] +
	champ->instruction.instruction[2];
      jump = champ->begin_instru + nbr;
      jump = check_if_overide(corewar, jump);
      if (check_registre(champ->instruction.instruction[3], 2) != 0)
	return (0);
      champ->registre[champ->instruction.instruction[3]] = get_four_bytes(jump);
      champ->wait_cycle = 0;
      clean_instruction(champ);
    }
  return (0);
}
