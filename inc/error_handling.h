#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H
# include "minishell.h"

# define ARGC_ERR "*****Welcome to Minishell*****\n\n \
Minishell doesn't need any args"
# define MALLOC_ERR "ERROR: Malloc error detected"
# define NOENV_ERR "Sorry, env is empty. Bye"
# define ENV_ALLOC_ERR "ERROR: Nothing was extracted from envp"
# define NOTFOUND_ERR "command not found"
# define FD_ACCESS_ERR "Permission denied"
# define FD_NONEX_ERR "No such file or directory"
# define HERE_STOP_ERR "here-document delimited by end-of-file, wanted"
# define TOKEN_ERR "syntax error near unexpected token"
# define EXEC_ERR "exec error detected. try again"
# define ISDIR_ERR "Is a directory"

/*error_handling*/
int			error_msg(char *cmd, char *arg, char *msg, int ret);
int			ft_error(char *msg, t_data *data);
int			set_exstat(t_parse *cmd_line, bool *execute, int status);
t_status	print_warning(t_parse *cmdl, t_status err);

#endif