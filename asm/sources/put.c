/*
** put.c for corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar/asm
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Sun Apr 12 14:10:49 2015 Boulay Arnaud
** Last update Sun Apr 12 18:42:33 2015 Boulay Arnaud
*/

#include <stdlib.h>
#include "asm.h"
#include "op.h"

int		put_label(int dest, int bytes, char *name, t_label *label_list)
{
  int		nb;
  t_label	*tmp;

  tmp = label_list->next;
  nb = -1;
  while (tmp != label_list)
    {
      if (nb == -1 && my_strcmp(tmp->name, name) == 1 && tmp->role == 0)
	{
	  nb = tmp->bytes;
	  tmp = label_list;
	}
      else if (nb > -1 && my_strcmp(tmp->name, name) == 1 && tmp->role == 1)
	{
	  put_int(dest, nb - tmp->bytes, bytes);
	  tmp->role = 2;
	  return (0);
	}
      tmp = tmp->next;
    }
  return (0);
}

int		put_codage(int dest, char **param)
{
  int		i;
  int		byte;

  byte = 0;
  i = 0;
  while (param[i] != NULL && i < MAX_ARGS_NUMBER)
    {
      if (param[i][0] == 'r')
	byte = (1 | byte) << 2;
      else if (param[i][0] == DIRECT_CHAR)
	byte = (2 | byte) << 2;
      else
	byte = (3 | byte) << 2;
      ++i;
    }
  if (i == 2)
    byte = byte << 2;
  my_putchar(byte, dest);
  return (0);
}

int		put_params(int dest, char *name, char **param, t_label *label_list)
{
  int		i;

  i = -1;
  while (param[++i] != NULL && i < MAX_ARGS_NUMBER)
    put_param_core(dest, param[i], name, label_list);
  return (0);
}

int		put_raw(int dest, char **line)
{
  int		i;

  i = 0;
  while (line[++i] != NULL)
    my_putchar(my_atoi_base(line[i], BASE16), dest);
  return (0);
}

int		put_opocode(int dest, char *code)
{
  int		i;

  i = 0;
  while (op_tab[i].mnemonique != NULL &&
	 my_strcmp(op_tab[i].mnemonique, code) != 1)
    ++i;
  if (op_tab[i].mnemonique == NULL)
    return (-1);
  else
    my_putchar(op_tab[i].code, dest);
  return (0);
}
