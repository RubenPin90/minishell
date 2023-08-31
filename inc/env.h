
#ifndef ENV_H
# define ENV_H
# include "minishell.h"

/*env_create*/
t_lstenv	*lstenv_new(char *cont);
t_lstenv    *copy_envp(char **env_org);
void        env_extract(t_lstenv **lst, t_lstenv *new);

/*env_utils*/
int			print_env(t_data *data);
char		**list_to_arr(t_data *data, t_lstenv *lst);
char		*ft_strjoin_wrapper(char *key, char *value);

#endif