/*
** event.c for event in /home/danilo_d/semestre2/no_message
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Sat Apr 11 14:00:34 2015 danilov dimitri
** Last update Sun Apr 12 12:21:35 2015 Bocquet Celestin
*/

#include	"cw.h"

void		sdl_event()
{
  char		finish;
  SDL_Event	event;

  finish = 1;
  while (finish)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_KEYDOWN)
	{
	  if (event.key.keysym.sym == SDLK_ESCAPE)
	    finish = 0;
	}
      if (event.type == SDL_QUIT)
	finish = 0;
    }
}

void		sdl_poll_event()
{
  SDL_Event	event;

  SDL_PollEvent(&event);
  if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_ESCAPE)
	exit(EXIT_FAILURE);
    }
}
