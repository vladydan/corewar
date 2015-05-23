/*
** files.c for corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar/asm
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Sat Apr  4 22:31:50 2015 Boulay Arnaud
** Last update Sun Apr 12 18:48:30 2015 Boulay Arnaud
*/

#include <fcntl.h>
#include <stdlib.h>
#include "asm.h"

int	get_just_name(char *str)
{
  int	tmp;
  int	i;

  i = 0;
  tmp = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '/')
	tmp = i;
      ++i;
    }
  if (tmp == 0)
    return (0);
  return (tmp + 1);
}

int	create_new_file(int *dest, char *file_name)
{
  char	*new_name;

  file_name = file_name + get_just_name(file_name);
  if ((new_name = malloc(sizeof(file_name) + 300)) == NULL)
    {
      my_putstr("Error: Malloc failed in open_files.\n", 1);
      return (-1);
    }
  new_name = my_strncpy(new_name, file_name, my_strlen(file_name) - 3);
  new_name = my_strcat(new_name, ".cor");
  if ((*dest = open(new_name, O_CREAT | O_WRONLY,
		    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) == -1)
    {
      my_putstr("Error: Couldn't create file ", 1);
      my_putstr(new_name, 1);
      my_putchar('\n', 1);
      return (-1);
    }
  free(new_name);
  return (0);
}

int	open_files(int *src, int *dest, char *file_name)
{
  if ((*src = open(file_name, O_RDONLY)) == -1)
    {
      my_putstr("Error: File ", 1);
      my_putstr(file_name, 1);
      my_putstr(" not accessible.\n", 1);
      return (-1);
    }
  if (file_name[my_strlen(file_name) - 1] != 's' ||
      file_name[my_strlen(file_name) - 2] != '.')
    {
      my_putstr("Error: file ", 1);
      my_putstr(file_name, 1);
      my_putstr(" is not a .s file.\n", 1);
      return (-1);
    }
  if (create_new_file(dest, file_name) == -1)
    return (-1);
  return (0);
}
