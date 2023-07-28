#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H
# include "minishell.h"

# define SUCCESS 0
# define FAIL 1
# define ARGC_ERR "*****Welcome to Minishell*****\n\n \
minishell doesn't need any args"
# define MALLOC_ERR "ERROR: Malloc error detected"
# define NOENV_ERR "Sorry, envp is empty. Bye"
# define ENV_ALLOC_ERR "ERROR: Nothing was extracted from envp"


void		ft_error(char *msg, t_data *data);
void	ft_cleanup(t_data **data);
void	free_null(void *ptr);
void	lstenv_clear(t_lstenv **head);

#endif