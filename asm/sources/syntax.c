/*
** syntax.c for corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar/asm
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Sun Apr  5 16:04:06 2015 Boulay Arnaud
** Last update Sun Apr 12 14:24:43 2015 Boulay Arnaud
*/

#include <stdlib.h>
#include "asm.h"
#include "op.h"

int		check_instruction(char **tab, int i, op_t code, t_label *label_list)
{
  int		bytes_param;
  int		bytes;
  char		*catted;
  char		**param;

  param = NULL;
  bytes = 1;
  if ((catted = my_cattab(tab, i, 0)) == NULL)
    return (-1);
  if ((param = my_strtowordtab(param, catted, SEPARATOR_CHAR)) == NULL)
    return (-1);
  free(catted);
  if (my_tablen(param) != code.nbr_args)
    {
      my_putstr("Syntax Error: Invalid arguments number.\n", 1);
      return (-1);
    }
  if (my_strcmp(tab[i], "live") == 0 && my_strcmp(tab[i], "zjmp") == 0 &&
      my_strcmp(tab[i], "fork") == 0)
    ++bytes;
  if ((bytes_param = check_params(tab[i], param, code, label_list)) == -1)
    return (-1);
  bytes = bytes + bytes_param;
  free_tab(param);
  return (bytes);
}

int		check_code(char **tab, int line_nb, int *total, t_label *label_list)
{
  int		tot_tmp;
  int		j;
  int		i;

  i = 0;
  j = 0;
  if (tab[i][my_strlen(tab[i]) - 1] == LABEL_CHAR)
    {
      tab[i][my_strlen(tab[i]) - 1] = '\0';
      if (check_label(tab[i], label_list, 0, *total) == -1)
	return (-1);
      ++i;
    }
  while (op_tab[j].mnemonique != NULL &&
	 my_strcmp(op_tab[j].mnemonique, tab[i]) != 1)
    ++j;
  if (op_tab[j].mnemonique == NULL ||
      (tot_tmp = check_instruction(tab, i, op_tab[j], label_list)) == -1)
    {
      my_putstr("Program stopped because of Syntax Error line ", 1);
      my_putnbr(line_nb, 1);
      return (-1);
    }
  set_label(label_list, total, tot_tmp);
  return (0);
}

int		check_strings(char **tab, int line_nb, int *start)
{
  int		ret;

  if (*start == 0)
    ret = my_strcmp(tab[0], NAME_CMD_STRING);
  else if (*start == 1)
    ret = my_strcmp(tab[0], COMMENT_CMD_STRING);
  if (ret == 2)
    {
      my_putstr("Syntax Error: line ", 1);
      my_putnbr(line_nb, 1);
      my_putstr(".\n", 1);
      return (-1);
    }
  else if (ret == 1)
    ++*start;
  else
    {
      my_putstr("Error: Can't find string .name or .comment\n", 1);
      return (-1);
    }
  return (0);
}

int		check_line(char **tab, int *total, int line_nb, t_label *label_list)
{
  static int	start = 0;

  if (tab[0] == NULL || tab[0][0] == COMMENT_CHAR)
    return (0);
  if (start < 2)
    {
      if (check_strings(tab, line_nb, &start) == -1)
	return (-1);
    }
  else
    if (check_line_core(tab, total, line_nb, label_list) == -1)
      return (-1);
  return (0);
}

int		check_syntax(int fd, int *total, t_label *label_list)
{
  int		line_nb;
  char		**line;
  char		*str;

  line_nb = 1;
  while ((str = get_next_line(fd)) != NULL)
    {
      if ((line = my_strtowordtab(line, str, ' ')) == NULL)
	{
	  my_putstr("Error: Malloc failed in my_strtowordtab.\n", 1);
	  return (-1);
	}
      free(str);
      if (check_line(line, total, line_nb, label_list) == -1)
	return (-1);
      free_tab(line);
      ++line_nb;
    }
  if (check_no_label(label_list) == -1)
    return (-1);
  return (0);
}
