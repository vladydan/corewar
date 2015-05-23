/*
** load_sdl.c for load_sdl in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Sun Apr 12 15:49:10 2015 danilov dimitri
** Last update Sun Apr 12 23:09:42 2015 Boulay Arnaud
*/

#include	"cw.h"

int		aff_Kappa(t_corewar *corewar, int flag, SDL_Rect pos)
{
  pos.x += 280;
  pos.y -= 20;
  if (flag == 1)
    SDL_BlitSurface(corewar->sdl.Kappa, NULL,
		    corewar->sdl.screen, &pos);
  if (flag == 0)
    SDL_BlitSurface(corewar->sdl.i_cry_everitim, NULL,
		    corewar->sdl.screen, &pos);
  return (0);
}

int		aff_win_or_lose(t_corewar *corewar, int nbr, int flag)
{
  SDL_Surface	*text;
  SDL_Rect	pos;

  pos.x = nbr * 375;
  pos.y = 850;
  if (nbr == 0)
    text = TTF_RenderText_Shaded(corewar->sdl.police2, corewar->champ.name[nbr],
				 corewar->sdl.blue, corewar->sdl.white);
  else if (nbr == 1)
    text = TTF_RenderText_Shaded(corewar->sdl.police2, corewar->champ.name[nbr],
				 corewar->sdl.green, corewar->sdl.white);
  else if (nbr == 2)
    text = TTF_RenderText_Shaded(corewar->sdl.police2, corewar->champ.name[nbr],
				 corewar->sdl.red, corewar->sdl.white);
  else if (nbr == 3)
    text = TTF_RenderText_Shaded(corewar->sdl.police2, corewar->champ.name[nbr],
				 corewar->sdl.yellow, corewar->sdl.white);
  else
    return (0);
  SDL_BlitSurface(text, NULL, corewar->sdl.screen, &pos);
  SDL_FreeSurface(text);
  aff_Kappa(corewar, flag, pos);
  SDL_Flip(corewar->sdl.screen);
  return (0);
}

void		init_color(t_corewar *corewar)
{
  corewar->sdl.color.r = 0x99;
  corewar->sdl.color.g = 0;
  corewar->sdl.color.b = 0;
  corewar->sdl.white.r = 0;
  corewar->sdl.white.g = 0;
  corewar->sdl.white.b = 0;
  corewar->sdl.blue.r = 0;
  corewar->sdl.blue.g = 0;
  corewar->sdl.blue.b = 255;
  corewar->sdl.green.r = 0;
  corewar->sdl.green.g = 0xCC;
  corewar->sdl.green.b = 0x33;
  corewar->sdl.red.r = 0xFF;
  corewar->sdl.red.g = 0;
  corewar->sdl.red.b = 0;
  corewar->sdl.yellow.r = 0xFF;
  corewar->sdl.yellow.g = 0xFF;
  corewar->sdl.yellow.b = 0;
}

int		init_sdl(t_corewar *corewar)
{
  if ((corewar->sdl.police = TTF_OpenFont("sprites/Starjedi.ttf", 20)) == NULL)
    return (-1);
  TTF_SetFontStyle(corewar->sdl.police, TTF_STYLE_NORMAL);
  if ((corewar->sdl.police2 = TTF_OpenFont("sprites/police_test.ttf", 15))
      == NULL)
    return (-1);
  TTF_SetFontStyle(corewar->sdl.police2, TTF_STYLE_NORMAL);
  if ((corewar->sdl.Kappa = SDL_LoadBMP("sprites/kappa_vm.bmp")) == NULL)
    return (-1);
  if ((corewar->sdl.i_cry_everitim = SDL_LoadBMP("sprites/BibleThump.bmp"))
      == NULL)
    return (-1);
  init_color(corewar);
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) < 0)
    return (-1);
  if ((corewar->sdl.music = Mix_LoadMUS("sprites/mortal.ogg")) == NULL)
    return (-1);
  Mix_PlayMusic(corewar->sdl.music, 1);
  corewar->sdl.color.r = 0x99;
  corewar->sdl.color.g = 0;
  corewar->sdl.color.b = 0;
  return (0);
}
