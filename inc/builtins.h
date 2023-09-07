
#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

/*builtins*/
int		check_builtin(t_parse *cmd_line, char *cmd);
int		builtin_parent(t_parse *cmd_line, char *cmd, int len);

/*builtin_cd*/
int		ft_cd(t_data *data);

/*builtin_echo*/
int		ft_echo(t_data *data);

/*builtin_exit*/
int		ft_exit(t_data *data);

/*builtin_export*/
int		ft_export(t_data *data);

/*builtin_pwd*/
int		ft_pwd(t_data *data);

/*builtin_unset*/
int		ft_unset(t_data *data);

# endif