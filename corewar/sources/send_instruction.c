/*
** send_instruction.c for send_intruction in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Fri Apr  3 15:00:36 2015 danilov dimitri
** Last update Sun Apr 12 12:40:00 2015 Bocquet Celestin
*/

#include	"cw.h"

t_ptr_inst	g_instru_choice[] =
  {
    {1, &live},
    {2, &ld},
    {3, &st},
    {4, &add},
    {5, &sub},
    {6, &and},
    {7, &or},
    {8, &xor},
    {9, &zjmp},
    {10, &ldi},
    {11, &sti},
    {12, &my_fork},
    {13, &lld},
    {14, &lldi},
    {15, &lfork},
    {16, &aff},
    {17, NULL},
  };

int		clean_instruction(t_champ *champ)
{
  int		i;

  i = -1;
  while (i != 3)
    {
      champ->instruction.instruction[i + 1] = 0;
      champ->instruction.type_instr[i] = 0;
      i++;
    }
  champ->instruction.instruction[0] = 20;
  return (0);
}

int		correct_instruction(t_champ *champ)
{
  int		i;
  unsigned char	*jmp;
  int		value;

  i = -1;
  while (++i != 3)
    {
      if (champ->instruction.type_instr[i] == 1)
	{
	  if (champ->instruction.instruction[i + 1] > REG_NUMBER ||
	      champ->instruction.instruction[i + 1] <= 0  )
	    return (-1);
	  champ->instruction.instruction[i + 1] =
	    champ->registre[champ->instruction.instruction[i + 1]];
	}
      if (champ->instruction.type_instr[i] == 2)
	{
	  jmp = champ->begin_instru + (champ->instruction.instruction[1 + 1]
				       % IDX_MOD);
	  value = get_four_bytes(jmp);
	  champ->instruction.instruction[i + 1] = value;
	}
    }
  return (0);
}

int		instruction(t_corewar *corewar, t_champ *champ)
{
  int		i;

  i = 0;
  while (g_instru_choice[i].num_instru != 17)
    {
      if (g_instru_choice[i].num_instru == champ->instruction.instruction[0])
	{
	  g_instru_choice[i].ptr(corewar, champ);
	}
      i++;
    }
  if (champ->instruction.instruction[0] == 0)
    champ->pc = check_if_overide(corewar, champ->pc + 1);
  return (0);
}
