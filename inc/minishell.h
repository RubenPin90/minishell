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
#include <sys/ioctl.h>

# include "structs.h"
# include "env.h"
# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtin.h"
# include "error_handling.h"
# include "tester.h"

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
void	handle_signals(bool heredoc);
void	receive_signal(int signum);

/*sys_input*/
int		handle_input(t_data *data);
int		check_quotes(char *str);

/*sys_init*/
void	init_data(t_data *data);

/*sys_utils*/
void	cmd_printer(t_data *data);
void	lexer_printer(t_lexer *lex, int check);
int		lex_len(t_lstenv *lst);
char	*ft_strjoin_wrapper(char *str1, char *str2, char *str3);
char	**arr_expand(char **arr, char *str);
int		ft_arrlen(char **arr);

/*sys_cleanup*/
void	ft_cleanup(t_data *data, bool check);
void	*free_null(void *ptr);
void	lstenv_clear(t_lstenv **head);
char	**free_arr(char **arr);
t_word	*free_word(t_word *word);

#endif