/*
** display.c for corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar/asm
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Sat Apr  4 19:24:11 2015 Boulay Arnaud
** Last update Sun Apr  5 20:58:56 2015 Boulay Arnaud
*/

#include <unistd.h>

void	my_putchar(char c, int fd)
{
  write(fd, &c, 1);
}

void	my_putstr(char *str, int fd)
{
  int	i;

  i = -1;
  while (str[++i] != '\0')
    my_putchar(str[i], fd);
}

void	my_putnbr(int nb, int fd)
{
  if (nb >= 10)
    my_putnbr(nb / 10, fd);
  my_putchar(nb % 10 + 48, fd);
}
