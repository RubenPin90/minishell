
#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

# define ARG_ERR "too many arguments"
# define NUM_ERR "numeric argument required"
# define CD_HOME_ERR "HOME not set"
# define CD_OLDPWD_ERR "OLDPWD not set"

/*builtins*/
int		check_builtin(t_parse *cmd_line, char *cmd);
int		builtin_parent(t_parse *cmd_line, char *cmd, int len);

/*builtin_cd*/
int		update_path(t_lstenv *env, char *pathname, char *key);
int		redir_pwd(t_data *data, t_lstenv *env, char *curpwd, char *key);
int		changedir(t_data *data, t_lstenv *env, char *curpwd, char *arg);
int		ft_cd(t_data *data, t_parse *cmd);

/*builtin_echo*/
int		write_args(char **args, int i, int size);
int		skip_nflags(char **args, int i, bool *newline);
int		ft_echo(t_data *data, t_parse *cmd);

/*builtin_exit*/
int		ft_exit(t_data *data, t_parse *cmd);

/*builtin_export*/
void	ft_bubsort(char **ar, t_lstenv *env);
int		ft_export(t_data *data, t_parse *cmd);
void	export_check(t_data *data, t_lexer *lex);
int		check_valid(char *arg, bool *equal);
int		update_env(t_lstenv *env, char *arg);

/*builtin_pwd*/
char	*get_pwd(void);
int		ft_pwd(t_data *data, t_parse *cmd);

/*builtin_unset*/
void	ft_find_n_del(t_lstenv **env, char *arg);
int		ft_unset(t_data *data, t_parse *cmd);

# endif