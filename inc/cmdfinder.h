#ifndef CMDFINDER_H
# define CMDFINDER_H
# include "minishell.h"

/*cmdfinder*/
int	cmdfinder(t_data *data, t_parse *cmd_line);
int	find_cmd(char **cmdpath, char **paths);

#endif