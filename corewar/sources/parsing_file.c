/*
** parsing_file.c for parsing_file in /home/danilo_d/semestre2/corewar_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Mon Mar 30 10:58:03 2015 danilov dimitri
** Last update Sun Apr 12 12:39:00 2015 Bocquet Celestin
*/

#include	"cw.h"
#include	"op.h"

int		is_alpha(char c)
{
  if (c >= 32 && c <= 126)
    return (1);
  return (0);
}

char		*find_string(int fd)
{
  char		buffer;
  char		*str;
  int		alpha;
  int		pos;

  pos = -1;
  alpha = 0;
  if ((str = malloc(COMMENT_LENGTH + 1)) == NULL)
    return (NULL);
  while ((read(fd, &buffer, 1) > 0))
    {
      if (is_alpha(buffer) == 1)
	{
	  str[++pos] = buffer;
	  alpha = 1;
	}
      else if (alpha == 1)
	{
	  str[pos + 1] = 0;
	  return (str);
	}
      if (pos > COMMENT_LENGTH)
	return (NULL);
    }
  return (NULL);
}

int		read_file(int fd, t_corewar *corewar, int *a, int i)
{
  int		ret;
  int		buffer;

  corewar->champ.begin_of_champ[i] = *a;
  lseek(fd, corewar->champ.pos_in_file[i], SEEK_SET);
  while ((ret = read(fd, &buffer, 1)))
    {
      corewar->memory.mem[*a] = buffer;
      corewar->memory.own_mem[*a] = i + 1;
      *a = *a + 1;
      if (*a > MEM_SIZE)
	{
	  my_putstr("Champion is too big\n");
	  exit(-1);
	}
    }
  return (0);
}

int		champion_too_big(int begin_mem, int tmp, int mem_champ)
{
  if (begin_mem - tmp > mem_champ)
    {
      my_putstr("Champion is too big\n");
      return (-1);
    }
  return (0);
}

int             inititialise_tab(t_corewar *corewar, char **argv, int begin)
{
  int		begin_mem;
  int		mem_champ;
  int		i;
  int		tmp;
  int		fd;

  i = -1;
  mem_champ = MEM_SIZE / (corewar->champ.nbr_champ - 1);
  if (reserve_memory(corewar) == -1)
    return (-1);
  begin_mem = 0;
  while (++i < corewar->champ.nbr_champ - 1)
    {
      fd = open(argv[i + 1 + begin], O_RDONLY);
      tmp = begin_mem;
      read_file(fd, corewar, &begin_mem, i);
      if (champion_too_big(begin_mem, tmp, mem_champ) == -1)
	return (-1);
      corewar->champ.end_of_champ[i] = begin_mem;
      begin_mem = tmp;
      close(fd);
      begin_mem += mem_champ;
    }
  aff_memory(corewar);
  return (0);
}
