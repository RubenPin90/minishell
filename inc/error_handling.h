#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H
# include "minishell.h"

# define ARGC_ERR "*****Welcome to Minishell*****\n\n \
Minishell doesn't need any args"
# define MALLOC_ERR "ERROR: Malloc error detected"
# define NOENV_ERR "Sorry, envp is empty. Bye"
# define ENV_ALLOC_ERR "ERROR: Nothing was extracted from envp"
# define NOTFOUND_ERR "command not found"
# define FD_ACCESS_ERR "Permission denied"
# define FD_NONEX_ERR "No such file or directory"
# define HERE_STOP_ERR "here-document delimited by end-of-file, wanted"

/*error_handling*/
int 	error_msg(char *cmd, char *arg, char *msg);
int		ft_error(char *msg, t_data *data);
void	switch_cmd_status(t_parse *cmd_line, bool *execute, t_status status);

#endif