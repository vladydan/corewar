/*
** main.c for main in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Sun Apr 12 16:22:57 2015 danilov dimitri
** Last update Sun Apr 12 20:51:05 2015 danilov dimitri
*/

#include	"op.h"
#include	"cw.h"

void		free_tab(char **tab)
{
  int		i;

  i = -1;
  while (tab[++i] != NULL)
    free(tab[i]);
  free(tab[i]);
  free(tab);
}

void		free_all(t_corewar *corewar)
{
  free_tab(corewar->champ.name);
  free_tab(corewar->champ.description);
  free(corewar->champion);
  free(corewar->memory.mem);
  free(corewar->memory.own_mem);
  free(corewar->champ.pos_in_file);
  free(corewar);
}

int		inititialise_champion(int argc, char **argv,
				      t_corewar *corewar, int begin)
{
  int		i;
  int		fd;

  i = -1;
  if ((corewar->champ.name = malloc(sizeof(char *) * argc)) == NULL  ||
      (corewar->champ.description = malloc(sizeof(char *) * argc)) == NULL ||
      (corewar->champ.pos_in_file = malloc(sizeof(int) * argc)) == NULL)
    return (-1);
  while (++i != argc - 1 - begin)
    {
      if ((fd = open(argv[i + 1 + begin], O_RDONLY)) <= 0)
	{
	  error_open(argv[i + 1 + begin]);
	  return (-1);
	}
      if ((corewar->champ.name[i] = find_string(fd)) == NULL ||
	  (corewar->champ.description[i] = find_string(fd)) == NULL)
	return (-1);
      corewar->champ.pos_in_file[i] = sizeof(header_t);
      close(fd);
    }
  corewar->champ.name[i] = NULL;
  corewar->champ.description[i] = NULL;
  corewar->champ.nbr_champ = i + 1;
  return (0);
}

int		main(int argc, char **argv)
{
  t_corewar	*corewar;
  int		begin;

  if ((corewar = malloc(sizeof(t_corewar))) == NULL)
    return (-1);
  if ((begin = prompt_error(argc, argv, corewar)) == -1)
    return (-1);
  if (error_file(argc, argv, begin) == -1)
    return (-1);
  if ((SDL_Init(SDL_INIT_VIDEO) != 0) || (TTF_Init() != 0) ||
      (corewar->sdl.screen = SDL_SetVideoMode
       (1500, 1000, 32, SDL_HWSURFACE)) == NULL)
    return (-1);
  if ((inititialise_champion(argc, argv, corewar, begin)) == -1)
    return (-1);
  if (inititialise_tab(corewar, argv, begin) == -1)
    return (-1);
  if (init_sdl(corewar) == -1)
    return (-1);
  main_corewar(corewar);
  sdl_event();
  free_all(corewar);
  TTF_Quit();
  SDL_Quit();
  return (0);
}
