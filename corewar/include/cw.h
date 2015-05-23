/*
** cw.h for cw in /home/danilo_d/semestre2/corewar_vm
**
** Made by danilov dimitri
** Login   <danilo_d@epitech.net>
**
** Started on  Sat Mar 28 17:23:33 2015 danilov dimitri
** Last update Sun Apr 12 19:56:44 2015 danilov dimitri
*/

#ifndef CW_H_
# define CW_H_

# include		<SDL/SDL.h>
# include		<SDL/SDL_ttf.h>
# include		<SDL/SDL_mixer.h>
# include		<stdlib.h>
# include		<sys/types.h>
# include		<sys/stat.h>
# include		<fcntl.h>
# include		<unistd.h>
# include		"op.h"

# define NEW_PROCESS	123456789
# define CHAMP_NUMBER	4

typedef union		s_union
{
  unsigned int		nbr;
  unsigned char		byte[4];
}			t_union;

typedef union		s_union_2
{
  unsigned int		nbr;
  unsigned char		byte[2];
}			t_union_2;

typedef struct		s_instruction
{
  int			instruction[4];
  int			type_instr[3];
}			t_instruction;

typedef struct		s_aff
{
  int			i;
  int			x;
  int			y;
  int			e;
  int			begin_mem;
  int			color;
}			t_aff;

typedef struct		s_champ
{
  t_instruction		instruction;
  char			*name;
  unsigned char		*begin_instru;
  int			nbr_champ;
  int			registre[REG_NUMBER];
  char			carry;
  unsigned char		*pc;
  int			wait_cycle;
  struct s_champ	*next;
  struct s_champ	*back;
}			t_champ;

typedef struct		s_tab_mem
{
  unsigned char		*mem;
  unsigned char		*own_mem;
  unsigned char		*end_memory;
  unsigned char		*begin_memory;
  char			live[CHAMP_NUMBER];
  int			actual_live;
  int			dump;
  int			nbr_process;
}			t_tab_mem;

typedef struct		s_champ_info
{
  char			**name;
  char			**description;
  int			*pos_in_file;
  int			begin_of_champ[CHAMP_NUMBER];
  int			end_of_champ[CHAMP_NUMBER];
  char			nbr_champ;
}			t_champ_info;

typedef struct		s_sdl
{
  SDL_Surface		*screen;
  SDL_Surface		*Kappa;
  SDL_Surface		*i_cry_everitim;
  TTF_Font		*police;
  SDL_Color		color;
  SDL_Color		white;
  SDL_Color		blue;
  SDL_Color		red;
  SDL_Color		yellow;
  SDL_Color		green;
  TTF_Font		*police2;
  Mix_Music		*music;
}			t_sdl;

typedef struct		s_corewar
{
  t_champ		*champion;
  t_champ_info		champ;
  t_tab_mem		memory;
  t_sdl			sdl;
}			t_corewar;

typedef struct		s_ptr_inst
{
  int			num_instru;
  int			(*ptr)(t_corewar *corewar, t_champ *champ);
}			t_ptr_inst;

int			my_strcpy(char * , char *, int);
int			sprint(int, char *);
int			my_putchar(char);
int			my_putstr(char *str);
char			*find_string(int fd);
int			my_strcmp(char *, char *);
int			my_getnbr(char *str);
int			my_strlen(char *);
int			reserve_memory(t_corewar *);
int			check_size(int a, int mem_champ);
int			inititialise_tab(t_corewar *corewar, char **argv,
					 int begin);
int			my_putstr(char *str);
void			setPixel(SDL_Surface *screen, int x, int y,
				 Uint32 color);
int			aff_memory(t_corewar *corewar);
int			main_corewar(t_corewar *corewar);
char			*my_strdup(char *);
void			aff_champ(t_champ *champ);
int			find_parameters(t_champ *champ);
int			parse_instruction(t_corewar *corewar, t_champ *champ);
int			find_one_parameter_2_byte(t_champ *champ);
int			find_one_parameter_4_byte(t_champ *champ);
int			find_sdi_lsi(t_champ *champ);
int			intruction(t_corewar *corewar, t_champ *champ);
int			live(t_corewar *core_ware, t_champ *champ);
int			ld(t_corewar *core_ware, t_champ *champ);
int			st(t_corewar *core_ware, t_champ *champ);
int			add(t_corewar *core_ware, t_champ *champ);
int			sub(t_corewar *core_ware, t_champ *champ);
int			and(t_corewar *core_ware, t_champ *champ);
int			or(t_corewar *core_ware, t_champ *champ);
int			xor(t_corewar *core_ware, t_champ *champ);
int			zjmp(t_corewar *core_ware, t_champ *champ);
int			ldi(t_corewar *core_ware, t_champ *champ);
int			sti(t_corewar *core_ware, t_champ *champ);
int			my_fork(t_corewar *core_ware, t_champ *champ);
int			lld(t_corewar *core_ware, t_champ *champ);
int			lldi(t_corewar *core_ware, t_champ *champ);
int			lfork(t_corewar *core_ware, t_champ *champ);
int			aff(t_corewar *core_ware, t_champ *champ);
int			overwrite_four_bytes(unsigned char *adress,
					     t_champ *champ, t_corewar *);
int			add_chain(t_champ *elem, t_corewar *corewar, int i);
void			rm_chain(t_champ *chain);
int			get_four_bytes(unsigned char *address);
unsigned char		*check_if_overide(t_corewar *corewar,
					  unsigned char *address);
int			error_file(int argc, char **argv, int);
int			instruction(t_corewar *corewar, t_champ *champ);
int			overwrite_four_bytes_st(unsigned char *adress, int nbr
						, t_champ *champ , t_corewar *);
int			create_child(t_champ *root, t_champ *champ, char opt);
int			correct_instruction(t_champ *champ);
int			error_open(char *str);
int			check_registre(int reg1, int reg2);
int			clean_instruction(t_champ *champ);
int			prompt_error(int argc, char **argv, t_corewar *corewar);
int			dump_memory(t_corewar *corewar);
void			aff_cycle(t_corewar *corewar, int nbr, int flag);
void			sdl_poll_event();
void			sdl_event();
int			aff_one_cycle(t_corewar *corewar, int nbr);
int			init_sdl(t_corewar *corewar);
int			aff_win_or_lose(t_corewar *corewar, int nbr, int flag);
int			print_live(char *str, int nbr, char *str2);
int			my_putnbr_base(unsigned char nb, char *base);
int			rm_champ(t_corewar *corewar, t_champ *champ,
				 char live_or_not[4], int i);
int			main_loop(t_corewar *corewar, int *cycle,
				  int *cycle_to_die, int *all_cycle);
int			add_two_parameter(t_champ *champ);

#endif /* !CW_H_ */
