/*
** live_ld_sd.c for live_ld_st in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Fri Apr  3 17:03:03 2015 danilov dimitri
** Last update Sun Apr 12 17:06:03 2015 danilov dimitri
*/

#include	"cw.h"

int		live(t_corewar *core_ware, t_champ *champ)
{
  if (champ->wait_cycle == 0)
    champ->wait_cycle = 10;
  else if (champ->wait_cycle > 1)
    champ->wait_cycle--;
  else if (champ->wait_cycle == 1)
    {
      if (champ->nbr_champ == champ->instruction.instruction[1])
	print_live("player %d (%s) is alive\n", champ->nbr_champ, champ->name);
      core_ware->memory.live[champ->nbr_champ - 1] = 1;
      core_ware->memory.actual_live++;
      clean_instruction(champ);
      champ->wait_cycle = 0;
    }
  return (0);
}

int		ld_2(t_corewar *core_ware, t_champ *champ)
{
  unsigned char	*jmp;
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
      jmp = champ->begin_instru + (champ->instruction.instruction[1]
				   % IDX_MOD);
      jmp = check_if_overide(core_ware, jmp);
      value = get_four_bytes(jmp);
      champ->registre[champ->instruction.instruction[2]] = value;
    }
  if (champ->instruction.type_instr[0] == 4)
    champ->registre[champ->instruction.instruction[2]] =
      champ->instruction.instruction[1];
  return (0);
}

int		ld(t_corewar *core_ware, t_champ *champ)
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
      ld_2(core_ware, champ);
      clean_instruction(champ);
    }
  return (0);
}

int		st_2(t_corewar *core_ware, t_champ *champ)
{
  unsigned char	*jmp;

  if (champ->instruction.type_instr[1] == 1)
    {
      if (check_registre(champ->instruction.instruction[2],
			 champ->instruction.instruction[1]) == -1)
	return (0);
      champ->registre[champ->instruction.instruction[2]] =
	champ->registre[champ->instruction.instruction[1]];
    }
  if (champ->instruction.type_instr[1] == 2)
    {
      jmp = champ->begin_instru +
	(champ->instruction.instruction[2] % IDX_MOD);
      if (check_registre(champ->instruction.instruction[1], 2) != 0)
	return (0);
      overwrite_four_bytes_st(jmp, champ->registre
			      [champ->instruction.instruction[1]],
			      champ, core_ware);
    }
  return (0);
}

int		st(t_corewar *core_ware, t_champ *champ)
{
  if (champ->wait_cycle == 0)
    champ->wait_cycle = 8;
  else if (champ->wait_cycle > 1)
    champ->wait_cycle--;
  else if (champ->wait_cycle == 1)
    {
      champ->wait_cycle = 0;
      st_2(core_ware, champ);
      clean_instruction(champ);
    }
  return (0);
}
