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

# include "structs.h"
# include "lexer.h"
# include "buildins.h"
# include "env.h"
# include "error_handling.h"
# include "parser.h"
# include "cmdfinder.h"
# include "executer.h"
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
void	handle_signals();
void	receive_signal(int signum, siginfo_t *info, void *context);

/*sys_input*/
int		handle_input(t_data *data);
int		check_quotes(char *str);

/*sys_init*/
void	init_data(t_data *data);

/*sys_utils*/
void	cmd_printer(t_data *data);
void	lexer_printer(t_data *data);
int	lex_len(t_lstenv *lst);

#endif