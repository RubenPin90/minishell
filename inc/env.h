
#ifndef ENV_H
# define ENV_H
# include "minishell.h"

void        print_env(t_lstenv *lst);
t_lstenv	*lstenv_new(char *cont);
t_lstenv    *copy_envp(char **env_org);
void        env_extract(t_lstenv **lst, t_lstenv *new);

#endif