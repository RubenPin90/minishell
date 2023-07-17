
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <libft.h>
# include "structs.h"
# include "lexer.h"
# include "buildins.h"
# include "env.h"


/*signals*/
void	handle_signals();
void	receive_signal(int signum, siginfo_t *info, void *context);

/*input*/
int		handle_input(t_data *data);

#endif