/*
** corewar.c for corewar in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Tue Mar 31 08:38:19 2015 danilov dimitri
** Last update Sun Apr 12 22:42:20 2015 Boulay Arnaud
*/

#include	"cw.h"

int		rm_dead_champ(char live_or_not[4], t_champ *champ,
			      t_corewar *corewar)
{
  int		i;
  int		nbr_live;

  i = -1;
  nbr_live = 0;
  while (++i < corewar->champ.nbr_champ - 1)
    {
      if (live_or_not[i] == 1)
	{
	  nbr_live++;
	  aff_win_or_lose(corewar, i, 1);
	}
      else if (live_or_not[i] != 2)
	rm_champ(corewar, champ, live_or_not, i);
    }
  return (nbr_live);
}

int		who_is_alive(t_champ *champ, t_corewar *corewar,
		     int all_cycle, int cycle_to_die)
{
  int		nbr_alive;
  int		i;

  i = -1;
  nbr_alive = rm_dead_champ(corewar->memory.live, champ, corewar);
  aff_memory(corewar);
  aff_cycle(corewar, cycle_to_die, 0);
  aff_cycle(corewar, all_cycle, 1);
  SDL_Flip(corewar->sdl.screen);
  if (nbr_alive >= 2)
    {
      while (++i != 4)
	corewar->memory.live[i] = 0;
      return (nbr_alive);
    }
  else if (nbr_alive == 0)
    {
      my_putstr("Tie\n");
      return (-1);
    }
  while (++i != 4)
    if (corewar->memory.live[i] == 1)
      print_live("Player %d (%s) won this game\n", i + 1,
		 corewar->champ.name[i]);
  return (-1);
}

t_champ		*create_list()
{
  t_champ	*base;

  if ((base = malloc(sizeof(t_champ))) == NULL)
    return (NULL);
  base->back = base;
  base->next = base;
  return (base);
}

int		initialise_list(t_corewar *corewar)
{
  int		i;

  i = -1;
  if ((corewar->champion = create_list()) == NULL)
    return (-1);
  corewar->memory.nbr_process = 0;
  while (++i != (corewar->champ.nbr_champ - 1))
    {
      corewar->memory.nbr_process++;
      if (add_chain(corewar->champion, corewar, i) == -1)
	return (-1);
    }
  return (0);
}

int		main_corewar(t_corewar *corewar)
{
  int		cycle;
  int		cycle_to_die;
  int		all_cycle;
  int		ret;

  cycle_to_die = CYCLE_TO_DIE;
  cycle = 0;
  all_cycle = 0;
  if (initialise_list(corewar) == -1)
    return (-1);
  while (cycle_to_die > 5)
    {
      cycle = 0;
      if (main_loop(corewar, &cycle, &cycle_to_die, &all_cycle) == -1)
	return (0);
      all_cycle += cycle;
      if ((ret= who_is_alive(corewar->champion, corewar,
			     all_cycle, cycle_to_die)) == -1)
	return (0);
    }
  if (ret >= 2)
    my_putstr("Tie\n");
  return (0);
}
