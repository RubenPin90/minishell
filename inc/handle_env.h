
#ifndef HANDLE_ENV_H
# define HANDLE_ENV_H
# include "minishell.h"

int			print_env(t_data *data);
t_lstenv	*lstenv_new(char *cont);
t_lstenv    *copy_envp(char **env_org);
void        env_extract(t_lstenv **lst, t_lstenv *new);

#endif