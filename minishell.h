/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:02 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/31 00:30:15 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFFER_SIZE 5
# include "libft/libft.h"
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct		s_rdata
{
	char			*file_name;
	char			*redir_type;
	struct s_rdata	*next;
	int				red_fd;
}					t_rdata;

typedef struct		s_data
{
	char			**envp;
	char			**args;
	int				err_status;
	struct s_data	*pipe;
	int				fd0;
	int				fd1;
	t_rdata			*redirects;
	pid_t			pid;
	int				signal;
}					t_data;

typedef struct		s_semdata
{
	int				previous_semicolon_position;
	char			**parsed_by_semicolon;
	char			*line;
}					t_semdata;

void				start(char *line, t_data *vars);
char				*add_char(char *str, char symb);
char				*variable_handler(char *str, char *dst, \
								int *iterator, t_data *vars);
char				*one_comma_worker(int *i, char *buffer, char *str);
char				*two_comma_worker(int *i, char *buffer, \
										char *str, t_data *vars);
int					get_next_line(int fd, char **line);
char				**semicolon(char *line, char parse_symb);
char				**ft_realloc_2arr(char **arr, int prev_size, int size);
int					get_amount_line(char **lines);
void				*ft_realloc(void *ptr, int size, int newsize);
char				**add_elem_in_arraystr(char **src, char *elem);
char				**delete_elem_in_arraystr(char **src, \
												char *elem, int bool_fp);
char				*find_elem_in_arraystr(char **src, char *elem, int bool_fp);
char				*get_value_from_var(char **envp, char *name_var);
char				**ft_strdup_2arr(char **arr);
void				ft_free_array(char ***ar);
int					in_screening(char *line, int symb_id);
void				replace_elem_in_envp(char **src,\
								char *name_variable, char *replace);
char				*get_name_var_from_arg(char *argument);
void				insertion_sort(char **mass, int n);
t_data				*ft_init(char **content);
int					ft_command(t_data *vars);
int					in_commas(char *line, int symb_id, char comma_type);
int					pipe_handler(char *command, t_data *vars);
void				cmd_exec(t_data *vars);
char				*pars_one_arg(int *i, char *line, t_data *vars);
void				free_listof_pipes(t_data **lst);
void				take_out_spaces(char **parsed_by_semicolon, \
									int commands_amount);
void				parse_command(char *command, t_data *vars);
char				*redirect_handler(t_data *vars, char *line);
void				free_listof_redirects(t_rdata **lst);
void				ft_redadd_back(t_rdata **lst, t_rdata *new);
t_rdata				*ft_init_red(void);
int					do_redirects(t_data *vars);

/*
** Error_messages
*/

int					error_message_unset(char *invalid_arg);
int					error_message_exp(char *invalid_arg);
int					path_error(char *path);
int					error_check(char *line);
void				error_message_rel_path(t_data *vars, \
						int f_no_dir_and_exist, int f_have_rights);

/*
** Commands
*/

int					ft_echo(t_data *data);
int					ft_pwd();
int					ft_env(t_data *data);
int					ft_export(t_data *data);
int					ft_cd(t_data *data);
int					ft_exit(t_data *data, int is_pipe);
int					ft_unset(t_data *data);

#endif
