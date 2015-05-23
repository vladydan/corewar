/*
** error.c for error in /home/danilo_d/semestre2/derniere_save_de_lundi
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Thu Apr  9 11:47:14 2015 danilov dimitri
** Last update Sun Apr 12 20:31:34 2015 danilov dimitri
*/

#include	"cw.h"

int		prompt_error(int argc, char **argv, t_corewar *corewar)
{
  if (argc < 3 || argc > CHAMP_NUMBER + 3)
    {
      my_putstr("Usage : corewar [-dump nbr_cycle] champ_name\n");
      return (-1);
    }
  if (my_strcmp(argv[1], "-dump") == 0)
    {
      if (argc <= 3)
	{
	  my_putstr("Usage : corewar [-dump nbr_cycle] champ_name\n");
	  return (-1);
	}
      if (argv[2] != NULL)
	corewar->memory.dump = my_getnbr(argv[2]);
      else
	{
	  my_putstr("Usage : corewar [-dump nbr_cycle] champ_name\n");
	  return (-1);
	}
      return (2);
    }
  else if (argc > CHAMP_NUMBER + 1)
    return (-1);
  corewar->memory.dump = 2000000;
  return (0);
}

int		error_open(char *str)
{
  my_putstr(str);
  my_putstr(" is not accesible\n");
  return (0);
}

int		check_registre(int reg1, int reg2)
{
  if (reg1 >= REG_NUMBER || reg1 <= 0)
    return (-1);
  if (reg2 >= REG_NUMBER || reg2 <= 0)
    return (-1);
  return (0);
}
