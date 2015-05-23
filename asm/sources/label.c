/*
** label.c for corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar/asm
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Thu Apr  9 01:53:43 2015 Boulay Arnaud
** Last update Fri Apr 10 16:34:22 2015 Boulay Arnaud
*/

#include "op.h"
#include "asm.h"

int		set_label(t_label *label_list, int *total, int tmp)
{
  t_label	*label_tmp;

  label_tmp = label_list->next;
  while (label_tmp != label_list)
    {
      if (label_tmp->bytes == 0)
	label_tmp->bytes = *total + 1;
      label_tmp = label_tmp->next;
    }
  *total = *total + tmp;
  return (0);
}

int		label_exist(char *label, t_label *label_list)
{
  t_label	*tmp;

  tmp = label_list->next;
  while (tmp != label_list)
    {
      if (my_strcmp(label, tmp->name) == 1 && tmp->role == 0)
	return (1);
      tmp = tmp->next;
    }
  return (0);
}

int		check_no_label(t_label *label_list)
{
  t_label	*tmp;

  tmp = label_list->next;
  while (tmp != label_list)
    {
      if (tmp->role == 1 && label_exist(tmp->name, label_list) == 0)
	{
	  my_putstr("Syntax Error: label ", 1);
	  my_putstr(tmp->name, 1);
	  my_putstr(" have no reference.\n", 1);
	  return (-1);
	}
      tmp = tmp->next;
    }
  return (0);
}

int		check_label(char *label, t_label *label_list, int role, int bytes)
{
  int		i;

  i = -1;
  while (label[++i] != '\0')
    if (is_inside(LABEL_CHARS, label[i]) == 0)
      {
	my_putstr("Syntax Error: Label ", 1);
	my_putstr(label, 1);
	my_putstr(" use other char than LABEL_CHARS.\n", 1);
	return (-1);
      }
  if (role == 0 && label_exist(label, label_list) == 1)
    {
      my_putstr("Syntax Error: Label ", 1);
      my_putstr(label, 1);
      my_putstr(" exist twice or more.", 1);
      return (-1);
    }
  if (add_chain(label_list, label, role, bytes) == -1)
    return (-1);
  return (0);
}
