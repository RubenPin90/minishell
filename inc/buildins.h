
#ifndef BUILDINS_H
# define BUILDINS_H
# include "minishell.h"

int		ft_pwd(t_data *data);
int		ft_exit(t_data *data);
int		check_buildin(t_parse *cmd_line, char *cmd);

# endif