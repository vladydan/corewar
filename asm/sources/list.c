/*
** list.c for corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Mon Apr  6 14:24:32 2015 Boulay Arnaud
** Last update Fri Apr 10 16:34:31 2015 Boulay Arnaud
*/

#include <stdlib.h>
#include "asm.h"

t_label		*create_list(void)
{
  t_label	*label_list;

  if ((label_list = malloc(sizeof(t_label))) == NULL)
    {
      my_putstr("Error: Malloc failed in create_list.\n", 1);
      return (NULL);
    }
  label_list->back = label_list;
  label_list->next = label_list;
  label_list->name = NULL;
  label_list->role = 0;
  label_list->bytes = 0;
  return (label_list);
}

int		add_chain(t_label *label_list, char *name, int role, int bytes)
{
  t_label	*new_chain;

  if (name == NULL)
    {
      my_putstr("Error: add_chain: name is NULL.\n", 1);
      return (-1);
    }
  if ((new_chain = malloc(sizeof(t_label))) == NULL)
    {
      my_putstr("Error: Malloc failed in add_chain.\n", 1);
      return (-1);
    }
  if ((new_chain->name = my_strdup(name)) == NULL)
    return (-1);
  new_chain->role = role;
  new_chain->bytes = bytes;
  if (new_chain->role == 0)
    ++new_chain->bytes;
  new_chain->back = label_list->back;
  new_chain->next = label_list;
  label_list->back->next = new_chain;
  label_list->back = new_chain;
  return (0);
}

void		rm_chain(t_label *chain)
{
  free(chain->name);
  chain->back->next = chain->next;
  chain->next->back = chain->back;
  free(chain);
}

void		rm_list(t_label *label_list)
{
  t_label	*chain;
  t_label	*tmp;

  chain = label_list->next;
  while (chain != label_list)
    {
      tmp = chain->next;
      rm_chain(chain);
      chain = tmp;
    }
  free(label_list);
}

void		empty_list(t_label *label_list)
{
  t_label	*chain;
  t_label	*tmp;

  chain = label_list->next;
  while (chain != label_list)
    {
      tmp = chain->next;
      rm_chain(chain);
      chain = tmp;
    }
}
