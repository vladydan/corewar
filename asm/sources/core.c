/*
** core.c for corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar/asm
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Sat Apr 11 23:03:31 2015 Boulay Arnaud
** Last update Sun Apr 12 18:45:34 2015 Boulay Arnaud
*/

#include <stdlib.h>
#include "asm.h"
#include "op.h"

void	put_param_core(int dest, char *param, char *name, t_label *label_list)
{
  int	bytes;

  bytes = sizeof(int);
  if (my_strcmp(name, "zjmp") == 1 || my_strcmp(name, "ldi") == 1 ||
      my_strcmp(name, "lldi") == 1 || my_strcmp(name, "sti") == 1 ||
      my_strcmp(name, "fork") == 1 || my_strcmp(name, "lfork") == 1 ||
      (param[0] != DIRECT_CHAR && param[0] != 'r'))
    bytes = 2;
  if (param[0] == 'r')
    my_putchar(my_atoi_base(param + 1, BASE10), dest);
  else if (param[0] == DIRECT_CHAR)
    if (param[1] == LABEL_CHAR)
      put_label(dest, bytes, param + 2, label_list);
    else if (param[1] == '0' && param[2] == 'x')
      put_int(dest, my_atoi_base(param + 3, BASE16), bytes);
    else
      put_int(dest, my_atoi_base(param + 1, BASE10), bytes);
  else
    if (param[0] == LABEL_CHAR)
      put_label(dest, bytes, param + 1, label_list);
    else if (param[0] == '0' && param[1] == 'x')
      put_int(dest, my_atoi_base(param + 2, BASE16), bytes);
    else
      put_int(dest, my_atoi_base(param, BASE10), bytes);
}

int	put_code(int dest, char **line, t_label *label_list)
{
  char	**param;
  char	*catted;
  int	i;

  i = 0;
  param = NULL;
  if (line[i][my_strlen(line[i]) - 1] == LABEL_CHAR)
    ++i;
  if (put_opocode(dest, line[i]) == -1)
    return (-1);
  if ((catted = my_cattab(line, i, 0)) == NULL)
    return (-1);
  if ((param = my_strtowordtab(param, catted, SEPARATOR_CHAR)) == NULL)
    return (-1);
  free(catted);
  if (my_strcmp(line[i], "live") == 0 && my_strcmp(line[i], "zjmp") == 0 &&
      my_strcmp(line[i], "fork") == 0)
    if (put_codage(dest, param) == -1)
      return (-1);
  if (put_params(dest, line[i], param, label_list) == -1)
    return (-1);
  free_tab(param);
  return (0);
}

int	put_line(int dest, char **line, t_label *label_list)
{
  if (line[0] == NULL || line[0][0] == COMMENT_CHAR)
    return (0);
  else if (my_strcmp(line[0], ".extend") == 1)
    return (0);
  else if (my_strcmp(line[0], ".code") == 1)
    put_raw(dest, line);
  else
    if (put_code(dest, line, label_list) == -1)
      return (-1);
  return (0);
}

int    create_core(int src, int dest, t_label *label_list)
{
  char	**line;
  char	*str;

  while ((str = get_next_line(src)) != NULL)
    {
      if ((line = my_strtowordtab(line, str, ' ')) == NULL)
	{
	  my_putstr("Error: Malloc failed in my_strtowordtab.\n", 1);
	  return (-1);
	}
      free(str);
      if (put_line(dest, line, label_list) == -1)
	return (-1);
      free_tab(line);
    }
  return (0);
}
