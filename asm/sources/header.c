/*
** header.c for corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar/asm
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Sat Apr  4 22:35:27 2015 Boulay Arnaud
** Last update Sun Apr 12 21:12:34 2015 Boulay Arnaud
*/

#include <stdlib.h>
#include <unistd.h>
#include "asm.h"
#include "op.h"

void		put_int(int dest, int nb, int max)
{
  int		i;
  t_tabint	tabint;

  tabint.nb = nb;
  i = max;
  while (--i >= 0)
    my_putchar(tabint.tab[i], dest);
}

void		write_str(int dest, char *name, int size)
{
  char		buff[size + 1];
  int		i;

  i = -1;
  set_buffer(buff, size);
  my_strncpy(buff, name + 1, my_strlen(name) - 3);
  while (++i != size)
    my_putchar(buff[i], dest);
}

int		choose_str(int dest, char **line, char *str, int total)
{
  if (my_strcmp(line[0], NAME_CMD_STRING) == 1)
    {
      if ((str = my_cattab(line, 0, 1)) == NULL)
	return (-1);
      write_str(dest, str, PROG_NAME_LENGTH);
      put_int(dest, 0, 4);
      put_int(dest, total, 4);
      free(str);
    }
  else if (my_strcmp(line[0], COMMENT_CMD_STRING) == 1)
    {
      if ((str = my_cattab(line, 0, 1)) == NULL)
	return (-1);
      write_str(dest, str, COMMENT_LENGTH);
      put_int(dest, 0, 4);
      free(str);
      return (1);
    }
  return (0);
}

int		put_str(int src, int dest, int total)
{
  int		ret;
  char		**line;
  char		*str;

  while ((str = get_next_line(src)) != NULL)
    {
      if ((line = my_strtowordtab(line, str, ' ')) == NULL)
	{
	  my_putstr("Error: Malloc failed in my_strtowordtab.\n", 1);
	  return (-1);
	}
      free(str);
      if ((ret = choose_str(dest, line, str, total)) == -1)
	return (-1);
      free_tab(line);
      if (ret == 1)
	return (0);
    }
  my_putstr("Error: Couldn't find .name or .comment.\n", 1);
  return (-1);
}

int		create_header(int src, int dest, t_label *label_list)
{
  int		ret;
  int		total;

  total = 0;
  if (check_syntax(src, &total, label_list) == -1)
    return (-1);
  if (total == 0)
    {
      my_putstr("Error: file is empty.\n", 1);
      return (-1);
    }
  while ((ret = lseek(src, -1, SEEK_CUR)))
    if (ret == -1)
      {
	my_putstr("Error: lseek failed in create_header.\n", 1);
	return (-1);
      }
  put_int(dest, COREWAR_EXEC_MAGIC, 4);
  if (put_str(src, dest, total) == -1)
    return (-1);
  return (0);
}
