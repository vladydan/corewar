/*
** add_to_list.c for add_to_list in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Sun Apr 12 13:58:53 2015 danilov dimitri
** Last update Sun Apr 12 13:58:54 2015 danilov dimitri
*/

#include "cw.h"

int		create_child(t_champ *root, t_champ *champ, char opt)
{
  t_champ	*new_elem;
  int		i;

  i = 1;
  if ((new_elem = malloc(sizeof(t_champ))) == NULL)
    exit(EXIT_FAILURE);
  new_elem->nbr_champ = champ->nbr_champ;
  if (opt == 0)
    new_elem->pc = champ->begin_instru +
      (champ->instruction.instruction[1] % IDX_MOD);
  if (opt == 1)
    new_elem->pc = champ->begin_instru + champ->instruction.instruction[1];
  if ((new_elem->name = my_strdup(champ->name)) == NULL)
    exit(EXIT_FAILURE);
  new_elem->wait_cycle = 0;
  new_elem->registre[1] = champ->registre[1];
  while (++i != REG_NUMBER)
    new_elem->registre[i] = champ->registre[i];
  new_elem->back = root->back;
  new_elem->next = root;
  root->back->next = new_elem;
  root->back = new_elem;
  return (0);
}

int		add_chain(t_champ *elem, t_corewar *corewar, int i)
{
  t_champ	*new_elem;
  int		j;

  if ((new_elem = malloc(sizeof(t_champ))) == NULL)
    return (-1);
  new_elem->nbr_champ = i + 1;
  if ((new_elem->name = my_strdup(corewar->champ.name[i])) == NULL)
    return (-1);
  new_elem->pc = &corewar->memory.mem[corewar->champ.begin_of_champ[i]];
  new_elem->wait_cycle = 0;
  new_elem->registre[1] = i + 1;
  j = 1;
  while (++j != REG_NUMBER)
    new_elem->registre[j] = 0;
  new_elem->back = elem->back;
  new_elem->next = elem;
  elem->back->next = new_elem;
  elem->back = new_elem;
  return (0);
}

void		rm_chain(t_champ *chain)
{
  chain->back->next = chain->next;
  chain->next->back = chain->back;
  free(chain->name);
  free(chain);
}
