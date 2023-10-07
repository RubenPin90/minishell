
#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

# define ARG_ERR "too many arguments"
# define NUM_ERR "numeric argument required"
# define CD_HOME_ERR "HOME not set"
# define CD_OLDPWD_ERR "OLDPWD not set"
# define INV_IDENT_ERR "not valid identifier"
# define INV_OPT_ERR "invalid option"

/*builtins_utils*/
int		is_builtin(t_parse *cmd_line, char *cmd);
int		builtin_parent(t_parse *cmd_line, char *cmd);

/*builtin_env*/
int		print_env(t_data *data, t_parse *cmd);
char	**list_to_arr(t_data *data, t_lstenv *lst);
char	*find_envkey(t_lstenv *env, char *var);
int		env_len(t_lstenv *lst);
void	print_env_arr(char **ar);

/*builtin_env_utils*/
int		ft_keylen(char *str);
void	ft_bubsort(char **ar, t_lstenv *env);
int		update_env(t_lstenv *env, char *arg, t_data *data);

/*builtin_cd*/
int		ft_cd(t_data *data, t_parse *cmd);
int		redir_pwd(t_data *data, t_lstenv *env, char *curpwd, char *key);
int		changedir(t_data *data, t_lstenv *env, char *curpwd, char *arg);
int		update_path(t_data *data, t_lstenv *env, char *pathname, char *key);
int		find_n_update(t_data *data, t_lstenv *env, char *nvalue, char *key);

/*builtin_echo*/
int		write_args(char **args, int i, int size);
int		skip_nflags(char **args, int i, bool *newline);
int		ft_echo(t_data *data, t_parse *cmd);

/*builtin_exit*/
int		ft_exit(t_data *data, t_parse *cmd);
int		check_exit(char *arg);

/*builtin_export*/
int		ft_export(t_data *data, t_parse *cmd);
int		check_exp_lst(t_lexer *exp_lst, t_lstenv *env, char *arg, t_data *data);
void	export_check(t_data *data, t_lexer *lex);
int		check_valid(char *arg, bool *equal);
int		export_error(int err, char *cmd);

/*builtin_pwd*/
char	*get_pwd(void);
int		ft_pwd(t_data *data, t_parse *cmd);

/*builtin_unset*/
void	ft_find_n_del(t_lstenv **env, char *arg);
int		ft_unset(t_data *data, t_parse *cmd);

# endif