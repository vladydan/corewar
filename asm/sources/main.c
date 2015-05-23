/*
** main.c for corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Mon Apr  6 14:26:01 2015 Boulay Arnaud
** Last update Sat Apr 11 23:03:25 2015 Boulay Arnaud
*/

#include <stdlib.h>
#include "asm.h"

int		my_asm(char *file_name)
{
  t_label	*label_list;
  int		src;
  int		dest;

  if (open_files(&src, &dest, file_name) == -1)
    return (-1);
  if ((label_list = create_list()) == NULL)
    return (-1);
  if (create_header(src, dest, label_list) == -1)
    return (-1);
  if (create_core(src, dest, label_list) == -1)
    return (-1);
  rm_list(label_list);
  return (0);
}

int		main(int ac, char **av)
{
  if (ac == 2)
    {
      if (my_asm(av[1]) == -1)
	return (-1);
    }
  else
    my_putstr("Usage: ./asm file_name.s\n", 1);
  return (0);
}
