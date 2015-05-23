/*
** fork_lfork_aff.c for fork in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Fri Apr  3 17:07:45 2015 danilov dimitri
** Last update Sun Apr 12 17:05:15 2015 danilov dimitri
*/

#include	"cw.h"

int		add_two_parameter(t_champ *champ)
{
  int		nbr;

  if (champ->instruction.type_instr[1] == 1
      && champ->instruction.type_instr[2] == 1)
    nbr = champ->registre[champ->instruction.instruction[2]]
      + champ->registre[champ->instruction.instruction[3]];
  if (champ->instruction.type_instr[1] == 1
      && champ->instruction.type_instr[2] == 2)
    nbr = champ->registre[champ->instruction.instruction[2]]
      + champ->instruction.instruction[3];
  if (champ->instruction.type_instr[1] == 2
      && champ->instruction.type_instr[2] == 1)
    nbr = champ->instruction.instruction[2]
      + champ->registre[champ->instruction.instruction[3]];
  if (champ->instruction.type_instr[1] == 2
      && champ->instruction.type_instr[2] == 2)
	nbr = champ->instruction.instruction[2]
	  + champ->instruction.instruction[3];
  return (nbr);
}

int		my_fork(t_corewar *core_ware, t_champ *champ)
{
  if (champ->wait_cycle == 0)
    champ->wait_cycle = 800;
  else if (champ->wait_cycle > 1)
    champ->wait_cycle--;
  else if (champ->wait_cycle == 1)
    {
      create_child(core_ware->champion, champ, 0);
      core_ware->memory.nbr_process++;
      champ->wait_cycle = 0;
      clean_instruction(champ);
    }
  return (0);
}

int		lfork(t_corewar *core_ware, t_champ *champ)
{
  if (champ->wait_cycle == 0)
    champ->wait_cycle = 1000;
  else if (champ->wait_cycle > 1)
    champ->wait_cycle--;
  else if (champ->wait_cycle == 1)
    {
	create_child(core_ware->champion, champ, 1);
      champ->wait_cycle = 0;
      clean_instruction(champ);
    }
  return (0);
}

int		aff(t_corewar *core_ware, t_champ *champ)
{
  int		character;

  if (champ->wait_cycle == 0)
    champ->wait_cycle = 2;
  else if (champ->wait_cycle > 1)
    champ->wait_cycle--;
  else if (champ->wait_cycle == 1)
    {
      (void)core_ware;
      if (check_registre(champ->instruction.instruction[1], 2) != 0)
	return (0);
      character = champ->registre[champ->instruction.instruction[1]] % 256;
      write(1, &character, 1);
      champ->wait_cycle = 0;
      clean_instruction(champ);
    }
  return (0);
}
