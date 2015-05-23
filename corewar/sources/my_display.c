/*
** my_display.c for display in /home/danilo_d/rendu/MUL_2014_fdf
**
** Made by Danilov Dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Sun Dec  7 12:18:41 2014 Danilov Dimitri
** Last update Sun Apr 12 12:31:26 2015 Bocquet Celestin
*/

#include	"cw.h"

int		print_live(char *str, int nbr, char *str2)
{
  int		i;

  i = -1;
  while (str[++i] != '\0')
    {
      if (str[i] == '%' && str[i + 1] == 's')
	{
	  my_putstr(str2);
	  i = i + 1;
	}
      else if (str[i] == '%' && str[i + 1] == 'd')
	{
	  my_putnbr_base(nbr, "0123456789");
	  i = i + 2;
	}
      else
	my_putchar(str[i]);
    }
  return (0);
}

int		my_putchar(char c)
{
  write(1, &c, 1);
  return (0);
}

int		my_putstr(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    {
      my_putchar(str[i]);
      i++;
    }
  return (0);
}

int		sprint(int nb, char str[100])
{
  int		i;
  int		divis;
  int		ret;
  int		j;

  j = 14;
  ret = 0;
  if (nb < 0)
    {
      ret = ret + my_putchar('-');
      nb = -nb;
    }
  divis = 1;
  while ((nb / divis) > 9)
    divis = divis *10;
  while (divis > 0)
    {
      i = (nb /divis) % 10;
      str[++j] = i + 48;
      divis = divis / 10;
    }
  str[++j] = ' ';
  str[++j] = ' ';
  str[++j] = 0;
  return (0);
}

void		setPixel(SDL_Surface *screen, int x, int y, Uint32 color)
{
  SDL_Rect	pixel;

  pixel.w = 1, pixel.h = 1;
  pixel.x = x, pixel.y = y;
  SDL_FillRect(screen, &pixel, color);
}
