#ifndef CMDFINDER_H
# define CMDFINDER_H
# include "minishell.h"

/*cmdfinder*/
int		check_binary(t_data *data, char **cmdpath);
int		cmdfinder(t_data *data, t_parse *cmd_line);
int		find_cmd(t_data *data, char **cmdpath, char **paths);
char	*find_envkey(t_lstenv *env, char *var);

#endif