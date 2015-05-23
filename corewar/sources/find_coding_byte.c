/*
** find_coding_byte.c for coding_byte in /home/danilo_d/semestre2/core_ware_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Thu Apr  2 14:24:12 2015 danilov dimitri
** Last update Sun Apr 12 21:42:24 2015 danilov dimitri
*/

#include	"cw.h"

int		*get_bits(int n)
{
  int		*bits;
  int		k;
  int		mask;
  int		masked_n;

  k = 0;
  if ((bits = malloc(sizeof(int) * 8)) == NULL)
    exit(EXIT_FAILURE);
  while (k < 8)
    {
      mask = 1 << k;
      masked_n = n & mask;
      bits[k] = masked_n >> k;
      k = k + 1;
    }
  return (bits);
}

int		find_sdi_lsi_2(t_champ *champ, int *coding_byte)
{
  int		i;
  int		j;

  j = 1;
  i = 7;
  while (i > -1)
    {
      if (coding_byte[i] == 0 && coding_byte[i - 1] == 1)
	{
	  champ->instruction.instruction[j] = *champ->pc;
	  champ->pc += 1;
	  champ->instruction.type_instr[j - 1] = 1;
	}
      else if (coding_byte[i] == 0 && coding_byte[i - 1] == 0);
      else
	{
	  champ->instruction.instruction[j] = find_one_parameter_2_byte(champ);
	  champ->instruction.type_instr[j - 1] = 2;
	}
      j++;
      i = i - 2;
    }
  return (0);
}

int		find_sdi_lsi(t_champ *champ)
{
  int		byte;
  int		*coding_byte;

  champ->pc += 1;
  byte = *champ->pc;
  coding_byte = get_bits(byte);
  champ->pc += 1;
  find_sdi_lsi_2(champ, coding_byte);
  free(coding_byte);
  return (0);
}

int		find_parameters2(t_champ *champ, int *coding_byte, int j)
{
  int		i;

  i = 7;
  while (i > -1)
    {
      if (coding_byte[i] == 0 && coding_byte[i - 1] == 1)
	{
	  champ->instruction.instruction[j] = *champ->pc;
	  champ->instruction.type_instr[j - 1] = 1;
	  champ->pc += 1;
	}
      if (coding_byte[i] == 1 && coding_byte[i - 1] == 0)
	{
	  champ->instruction.instruction[j] = find_one_parameter_4_byte(champ);
	  champ->instruction.type_instr[j - 1] = 4;
	}
      if (coding_byte[i] == 1 && coding_byte[i - 1] == 1)
	{
	  champ->instruction.instruction[j] = find_one_parameter_2_byte(champ);
	  champ->instruction.type_instr[j - 1] = 2;
	}
      j++;
      i = i - 2;
    }
  return (0);
}

int		find_parameters(t_champ *champ)
{
  int		byte;
  int		*coding_byte;
  int		j;

  j = 1;
  champ->pc += 1;
  byte = *champ->pc;
  if ((coding_byte = get_bits(byte)) == NULL)
    return (-1);
  champ->pc += 1;
  find_parameters2(champ, coding_byte, j);
  free(coding_byte);
  return (0);
}
