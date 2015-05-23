/*
** get_next_line.c for corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Sun Apr  5 16:20:55 2015 Boulay Arnaud
** Last update Sun Apr  5 21:54:22 2015 Boulay Arnaud
*/

#include <stdlib.h>
#include <unistd.h>
#include "asm.h"

int		gn_strlen(char *str)
{
  int		i;

  i = 0;
  if (str == NULL)
    return (-1);
  while (str[i] != '\0')
    i = i + 1;
  return (i);
}

char		*init_buffer(char *buffer, int j, int len)
{
  while (j != (len + BUFFER_SIZE + 1))
    {
      buffer[j] = '\0';
      j = j + 1;
    }
  return (buffer);
}

char		*gnl_remalloc(char *src)
{
  char		*dest;
  int		i;

  i = 0;
  dest = malloc(gn_strlen(src) + BUFFER_SIZE + 1);
  if (dest == NULL)
    return (NULL);
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      i = i + 1;
    }
  dest = init_buffer(dest, i, gn_strlen(src));
  free(src);
  return (dest);
}

char		*gnl_strcpy(char *dest, char *src, int *i, int *j)
{
  while (src[*j] == '\n')
    *j = *j + 1;
  while (src[*j] != '\0' && src[*j] != '\n')
    {
      dest[*i] = src[*j];
      *i = *i + 1;
      *j = *j + 1;
    }
  dest = gnl_remalloc(dest);
  return (dest);
}

char		*get_next_line(const int fd)
{
  char		*str;
  int		i;
  static int	ret = 1;
  static int	j = BUFFER_SIZE;
  static char	buffer[BUFFER_SIZE + 1];

  ret = 1;
  i = 0;
  if (((str = malloc(BUFFER_SIZE + 1)) == NULL) || BUFFER_SIZE == 0)
    return (NULL);
  str = init_buffer(str, 0, 0);
  while (ret > 0 && buffer[j] != '\n')
    if (buffer[j] == '\0' && init_buffer(buffer, 0, 0))
      {
	if (((ret = read(fd, buffer, BUFFER_SIZE)) <= 0) && gn_strlen(str) <= 0)
	  {
	    free(str);
	    return (NULL);
	  }
	j = 0;
      }
    else if (ret > 0 && (str = gnl_strcpy(str, buffer, &i, &j)) == NULL)
      return (NULL);
  ++j;
  return (str);
}
