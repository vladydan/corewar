/*
** check_tools.c for corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar/asm
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Thu Apr  9 12:34:36 2015 Boulay Arnaud
** Last update Sun Apr 12 19:06:21 2015 Boulay Arnaud
*/

#include <limits.h>
#include <stdlib.h>
#include "op.h"
#include "asm.h"

int	check_line_core(char **tab, int *total, int line_nb, t_label *label_list)
{
  if (my_strcmp(tab[0], ".extend") == 1)
    return (0);
  else if (my_strcmp(tab[0], ".code") == 1)
    {
      if (check_raw(tab, total) == -1)
	{
	  my_putstr("Syntax Error: Invalid params for .code at line ", 1);
	  my_putnbr(line_nb, 1);
	  my_putchar('\n', 1);
	  return (-1);
	}
    }
  else if (check_code(tab, line_nb, total, label_list) == -1)
    {
      my_putchar('\n', 1);
      return (-1);
    }
  if (*total <= INT_MIN)
    {
      my_putstr("Error: too much code in file.\n", 1);
      return (-1);
    }
  return (0);
}

int	param_execption(char *name, int i)
{
  if (my_strcmp(name, "zjmp") == 1)
    return (1);
  else if ((my_strcmp(name, "ldi") == 1 || my_strcmp(name, "lldi") == 1)
	   && (i == 1 || i == 2))
    return (1);
  else if ((my_strcmp(name, "sti") == 1) && (i == 2 || i == 3))
    return (1);
  else if (my_strcmp(name, "fork") == 1 || my_strcmp(name, "lfork") == 1)
    return (1);
  return (0);
}

int	add_bytes(char type, char b_param, int i, char *name)
{
  if ((b_param & type) == 0)
    {
      my_putstr("Syntax Error: Bad argument for instruction ", 1);
      my_putstr(name, 1);
      my_putstr(".\n", 1);
      return (-1);
    }
  if (b_param == 1)
    return (1);
  else if (b_param == 4 || param_execption(name, i) == 1)
    return (2);
  else if (b_param == 2)
    return (4);
  return (0);
}

char	**sort_params(char **tab, char *param)
{
  if (is_inside(param, '+') == 1)
    {
      if ((tab = my_strtowordtab(tab, param, '+')) == NULL)
	return (NULL);
    }
  else if (is_inside(param, '-') == 1)
    {
      if ((tab = my_strtowordtab(tab, param, '-')) == NULL)
	return (NULL);
    }
  else
    {
      if ((tab = my_strtowordtab(tab, param, ' ')) == NULL)
	return (NULL);
      if (tab[1] != NULL)
	return (NULL);
    }
  return (tab);
}

int	get_params(char *param, t_label *label_list)
{
  int	rslt;

  rslt = 0;
  if (param[0] == LABEL_CHAR)
    {
      if (check_label(param + 1, label_list, 1, 0) == -1)
	return (-1);
    }
  else if (param[0] == '0' && param[1] == 'x')
    {
      if ((rslt = my_atoi_base(param + 2, BASE16)) == -1)
	return (-1);
    }
  else
    if ((rslt = my_atoi_base(param, BASE10)) == -1)
      return (-1);
  return (rslt);
}
