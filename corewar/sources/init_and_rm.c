/*
** init_and_rm.c for init_and_rm.c in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Sun Apr 12 15:10:05 2015 danilov dimitri
** Last update Sun Apr 12 21:49:40 2015 danilov dimitri
*/

#include "cw.h"

int		rm_champ(t_corewar *corewar, t_champ *champ,
		 char live_or_not[4], int i)
{
  t_champ       *tmp;

  tmp = champ->next;
  live_or_not[i] = 2;
  aff_win_or_lose(corewar, i, 0);
  while (tmp != champ)
    {
      if (tmp->nbr_champ == i + 1)
	rm_chain(tmp);
      tmp = tmp->next;
    }
  return (0);
}

int		main_loop(t_corewar *corewar, int *cycle, int *cycle_to_die,
			  int *all_cycle)
{
  while (*cycle < *cycle_to_die)
    {
      parse_instruction(corewar, corewar->champion);
      while (corewar->memory.actual_live > NBR_LIVE)
	{
	  *cycle_to_die -= CYCLE_DELTA;
	  corewar->memory.actual_live -= NBR_LIVE;
	}
      *cycle += 1;
      if (*cycle % 10 == 0)
	aff_one_cycle(corewar, *cycle);
      if (*cycle + *all_cycle > corewar->memory.dump)
	{
	  dump_memory(corewar);
	  return (-1);
	}
      sdl_poll_event();
    }
  return (0);
}
