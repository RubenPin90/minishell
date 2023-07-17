#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <libft.h>
# include "structs.h"
# include "lexer.h"

/*signals*/
void	handle_signals();
void	receive_signal(int signum, siginfo_t *info, void *context);

/*input*/
int		handle_input(t_data *data);

/*utils*/
char	**copy_envp(char **env_org);

#endif