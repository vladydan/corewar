/*
** my_get_nbr.c for get_next_line in /home/danilo_d/rendu/MUL_2014_fdf
**
** Made by Danilov Dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Wed Dec  3 11:04:17 2014 Danilov Dimitri
** Last update Fri Apr 10 16:47:04 2015 danilov dimitri
*/

int	is_neg(char *str)
{
  int	i;
  int	counter;

  i = 0;
  counter = 0;
  while (str[i] > '9' || str[i] < '0')
    {
      if (str[i] == '-')
	counter = counter + 1;
      i = i + 1;
    }
  if (counter % 2 != 0)
    return (1);
  else
    return (0);
}

int	is_num(char l)
{
  if (l >= '0' && l <= '9')
    return (1);
  return (0);
}

int	my_getnbr(char *str)
{
  int	nbr;
  int	i;

  i = 0;
  nbr = 0;
  if (!str)
    return (0);
  while (is_num(str[i]) == 0)
    i = i + 1;
  while (is_num(str[i]) == 1)
    {
      nbr = ((nbr * 10) + (str[i] - 48));
      i = i + 1;
    }
  return (nbr);
}
