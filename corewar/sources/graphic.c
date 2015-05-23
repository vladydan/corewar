/*
** graphic.c for graphic in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Sun Apr 12 15:48:48 2015 danilov dimitri
** Last update Sun Apr 12 21:48:27 2015 danilov dimitri
*/

#include	"cw.h"
#include	"op.h"

int		put_big_square(t_corewar *corewar, unsigned int color, int x, int y)
{
  int		i;
  int		j;

  i = -1;
  while (++i != 12)
    {
      j = -1;
      while (++j != 12)
	setPixel(corewar->sdl.screen, y + j, x + i, color);
    }
  return (0);
}

void		init_variable(t_aff *aff)
{
  aff->color = 0x0000FF;
  aff->e = 0;
  aff->i = -1;
  aff->x = 0;
  aff->y = 0;
}

int		aff_memory(t_corewar *corewar)
{
  t_aff		aff;

  init_variable(&aff);
  while (++aff.i != MEM_SIZE)
    {
      if (corewar->memory.own_mem[aff.i] == 1)
	put_big_square(corewar, aff.color, aff.x, aff.y);
      else if (corewar->memory.own_mem[aff.i] == 2)
	put_big_square(corewar, 0x00CC33, aff.x, aff.y);
      else if (corewar->memory.own_mem[aff.i] == 3)
	put_big_square(corewar, 0xFF0000, aff.x, aff.y);
      else if (corewar->memory.own_mem[aff.i] == 4)
	put_big_square(corewar, 0xFFFF00, aff.x, aff.y);
      else
	put_big_square(corewar, 0xFFFFFF, aff.x, aff.y);
      aff.y += 13;
      if (aff.y > 1487)
	{
	  aff.y = 0;
	  aff.x += 13;
	}
    }
  SDL_Flip(corewar->sdl.screen);
  return (0);
}

void		aff_cycle(t_corewar *corewar, int nbr, int flag)
{
  SDL_Surface	*text;
  char		str[100];
  SDL_Rect	position;

  if (flag == 0)
    {
      position.x = 0;
      my_strcpy(str, "Cycle to Die : ", 15);
    }
  if (flag == 1)
    {
      my_strcpy(str, "Total Cycle   : ", 15);
      position.x = 500;
    }
  sprint(nbr, str);
  text = TTF_RenderText_Shaded(corewar->sdl.police, str,
			       corewar->sdl.color, corewar->sdl.white);
  position.y = 750;
  SDL_BlitSurface(text, NULL, corewar->sdl.screen, &position);
  SDL_FreeSurface(text);
}

int		aff_one_cycle(t_corewar *corewar, int nbr)
{
  SDL_Surface	*text;
  char		str[100];
  SDL_Rect	position;

  position.x = 1000;
  my_strcpy(str, "Cycle       :  ", 15);
  corewar->sdl.color.r = 0x99;
  corewar->sdl.color.g = 0;
  corewar->sdl.color.b = 0;
  sprint(nbr, str);
  text = TTF_RenderText_Shaded(corewar->sdl.police, str,
			       corewar->sdl.color, corewar->sdl.white);
  position.y =750;
  SDL_BlitSurface(text, NULL, corewar->sdl.screen, &position);
  SDL_FreeSurface(text);
  SDL_Flip(corewar->sdl.screen);
  return (0);
}
