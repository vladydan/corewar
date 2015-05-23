/*
** string.c for string in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Mon Apr  6 17:34:03 2015 danilov dimitri
** Last update Sun Apr 12 12:34:09 2015 Bocquet Celestin
*/

#include	"cw.h"

int		my_strcpy(char *dest, char *src, int size)
{
  int		i;

  i = -1;
  while (++i != size)
    dest[i] = src[i];
  return (0);
}

char		*my_strdup(char *src)
{
  int		i;
  char		*dest;

  i = 0;
  while (src[i] != '\0')
    i = i + 1;
  dest = malloc(i + 1);
  if (dest == NULL)
    return (NULL);
  i = 0;
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      i = i + 1;
    }
  dest[i] = '\0';
  return (dest);
}

int		my_strcmp(char *s1, char *s2)
{
  int		i;

  i = 0;
  while (s1[i] == s2[i])
    {
      if (s1[i] == '\0' && s2[i] == '\0')
	return (0);
      i = i + 1;
    }
  return (-1);
}

int		my_strlen(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}

int		error_file(int argc, char **argv, int begin)
{
  int		i;
  int		lengh;

  i = begin;
  while (++i != argc)
    {
      lengh = my_strlen(argv[i]);
      if (lengh < 4)
	{
	  my_putstr(argv[i]);
	  my_putstr(" is not a corewar executable\n");
	  return (0);
	}
      else if (my_strcmp(&argv[i][lengh - 4], ".cor") != 0)
	{
	  my_putstr(argv[i]);
	  my_putstr(" is not a corewar executable\n");
	  return (-1);
	}
    }
  return (0);
}
