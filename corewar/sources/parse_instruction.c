/*
** parse_instruction.c for parse_intructions in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Wed Apr  1 14:24:49 2015 danilov dimitri
** Last update Sun Apr 12 20:50:16 2015 danilov dimitri
*/

#include	"cw.h"

int		no_coding_byte(t_champ *champ)
{
  if (champ->instruction.instruction[0] == 1)
    {
      champ->pc += 1;
      champ->instruction.instruction[1] =
	find_one_parameter_4_byte(champ);
      return (1);
    }
  else if (champ->instruction.instruction[0] == 9 ||
	   champ->instruction.instruction[0] ==  12 ||
	   champ->instruction.instruction[0] ==  16 ||
	   champ->instruction.instruction[0] ==  15)
    {
      champ->pc += 1;
      champ->instruction.instruction[1] =
	find_one_parameter_2_byte(champ);
      return (1);
    }
  return (-1);
}

int		find_one_parameter_4_byte(t_champ *champ)
{
  t_union	uni;
  int		i;

  i = 4;
  uni.nbr = 0;
  while (--i != -1)
    {
      uni.byte[i] = *champ->pc;
      champ->pc +=1;
    }
  return (uni.nbr);
}

int		find_one_parameter_2_byte(t_champ *champ)
{
  t_union_2	uni;
  int		i;

  i = 2;
  uni.nbr = 0;
  while (--i != -1)
    {
      uni.byte[i] = *champ->pc;
      champ->pc += 1;
    }
  if (uni.byte[1] == 0xff)
    uni.nbr = - (uni.byte[1] - uni.byte[0]);
  return (uni.nbr);
}

int		parse_instruction(t_corewar *corewar, t_champ *champ)
{
  int		ret;
  t_champ	*tmp;

  tmp = champ->next;
  while (tmp != champ)
    {
      if (tmp->wait_cycle == 0)
	{
	  tmp->begin_instru = tmp->pc;
	  tmp->instruction.instruction[0] = *tmp->pc;
	  ret = no_coding_byte(tmp);
	  if ((tmp->instruction.instruction[0] == 11 ||
	       tmp->instruction.instruction[0] == 10) && ret != 1)
	    find_sdi_lsi(tmp);
	  else if (ret != 1)
	    find_parameters(tmp);
	}
      if (tmp->wait_cycle == NEW_PROCESS)
	tmp->wait_cycle = 0;
      else
	instruction(corewar, tmp);
      tmp = tmp->next;
    }
  return (0);
}
