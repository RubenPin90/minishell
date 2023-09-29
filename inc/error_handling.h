#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H
# include "minishell.h"

# define ARGC_ERR "*****Welcome to Minishell*****\n\n \
minishell doesn't need any args"
# define MALLOC_ERR "ERROR: Malloc error detected"
# define NOENV_ERR "Sorry, envp is empty. Bye"
# define ENV_ALLOC_ERR "ERROR: Nothing was extracted from envp"
# define NOTFOUND_ERR "command not found\n"
# define FD_ACCESS_ERR "Permission denied\n"
# define FD_NONEX_ERR "No such file or directory\n"


int		ft_error(char *msg, t_data *data);


/*error_utils*/
int 	error_msg(char *cmd, char *arg, char *msg);

#endif