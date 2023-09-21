
#ifndef ENV_H
# define ENV_H
# include "minishell.h"

/*env_create*/
t_lstenv    *copy_envp(char **env_org);
void        env_addback(t_lstenv **lst, t_lstenv *new);
t_lstenv	*lstenv_create(char *cont);
t_lstenv	*lstenv_new(char *key, char *value);

/*env_utils*/
int			print_env(t_data *data, t_parse *cmd);
char		**list_to_arr(t_data *data, t_lstenv *lst);
char		*find_envkey(t_lstenv *env, char *var);
int			env_len(t_lstenv *lst);
void		print_env_arr(char **ar);

#endif