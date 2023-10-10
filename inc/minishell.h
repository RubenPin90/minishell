/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:31:04 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 16:17:50 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <libft.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

# include "structs.h"
# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtin.h"
# include "error_handling.h"

/*colors*/
# define RESET "\e[0m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define PINK "\e[0;35m"

/*return values*/
# define STOP -1
# define SUCCESS 0
# define FAIL 1
# define AGAIN 2

/*signals*/
void		handle_signals(bool heredoc, bool child);
void		receive_signal(int signum);

/*sys_input*/
int			handle_input(t_data *data);

/*sys_init*/
void		init_data(t_data *data);

/*sys_utils*/
char		*ft_strjoin_wrapper(char *str1, char *str2, char *str3);
char		**arr_expand(char **arr, char *str);
int			ft_arrlen(char **arr);
int			is_executable(t_parse *cmdl);
int			tkn_counter(t_lexer *lex, t_type tkn, t_type end);

/*sys_cleanup*/
void		ft_cleanup(t_data *data, bool check);
void		*free_null(void *ptr);
void		lstenv_clear(t_lstenv **head);
char		**free_arr(char **arr);
t_word		*free_word(t_word *word);

/*sys_cleanup2*/
t_parse		*free_parser(t_parse *cmd_line);
void		free_lexer(t_lexer **lex);

/*sys_env_create*/
t_lstenv	*copy_envp(t_data *data, char **env_org);
int			env_addback(t_lstenv **lst, t_lstenv *new);
t_lstenv	*lstenv_create(char *cont);
t_lstenv	*lstenv_new(char *key, char *value);

#endif