/*
** asm.h for asm_corewar in /home/boulay_b/Rendu/SE2/CPE/CPE_2014_corewar/asm
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Mon Mar 30 09:34:18 2015 Boulay Arnaud
** Last update Sun Apr 12 19:00:48 2015 Boulay Arnaud
*/

#ifndef	ASM_H_
# define ASM_H_

# include "op.h"

# define BUFFER_SIZE	4096
# define BASE10		"0123456789"
# define BASE16		"0123456789ABCDEF"

typedef union		u_tabint
{
  int			nb;
  char			tab[sizeof(int)];
}			t_tabint;

typedef struct		s_label
{
  int			role;
  char			*name;
  int			bytes;
  struct s_label	*next;
  struct s_label	*back;
}			t_label;

int			my_tablen(char **tab);
int			my_atoi_base(char *str, char *base);
int			check_raw(char **tab, int *total);
int			check_code(char **tab, int line_nb, int *total,
				   t_label *label_list);
int			add_bytes(char type, char b_param, int i, char *name);
int			open_files(int *src, int *dest, char *file_name);
int			set_label(t_label *label_list, int *total, int tmp);
int			check_label(char *label, t_label *label_list, int role,
				    int bytes);
int			check_syntax(int fd, int *total, t_label *label_list);
int			check_params(char *name, char **param, op_t code,
				     t_label *label_list);
int			check_line_core(char **tab, int *total, int line_nb,
					t_label *label_list);
int			create_header(int src, int dest, t_label *label_list);
int			is_inside(char *str, char c);
int			put_codage(int dest, char **param);
int			put_params(int dest, char *name, char **param,
				   t_label *label_list);
int			put_label(int dest, int bytes, char *name,
				  t_label *label_list);
int			put_raw(int dest, char **line);
int			put_opocode(int dest, char *code);
int			create_core(int src, int dest, t_label *label_list);
int			my_strlen(char *str);
int			check_no_label(t_label *label_list);
int			add_chain(t_label *label_list, char *name, int role,
				  int bytes);
int			my_strcmp(char *str1, char *str2);
int			get_params(char *param, t_label *label_list);
char			*get_next_line(const int fd);
char			*my_cattab(char **tab, int i, int sep);
char			*my_strcat(char *dest, char *src);
char			*my_strdup(char *str);
char			*my_strncpy(char *dest, char *src, int n);
char			**my_strtowordtab(char **tab, char *str, char sep);
char			**sort_params(char **tab, char *str);
void			set_buffer(char *buff, int size);
void			put_int(int dest, int nb, int max);
void			my_putchar(char c, int fd);
void			my_putstr(char *str, int fd);
void			free_tab(char **tab);
void			my_putnbr(int nb, int fd);
void			rm_list(t_label *label_list);
void			put_param_core(int dest, char *param, char *name,
				       t_label *label_list);
t_label			*create_list(void);

#endif /* !ASM_H_ */
