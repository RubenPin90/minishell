#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

extern int	g_signum;

/*executor*/
int		exec_child(t_data *data, t_parse *cmd, char *cmdpath);
int		exec_builtin(t_data *data, t_parse *cmd, bool parent);
int		exec_single_cmd(t_parse *cmd, bool parent, t_data *data);
int		exec_multi_cmds(t_parse *cmd_line, int cmds, t_data *data);
int		executor(t_data *data);

/*exec_utils*/
int		create_pipes(t_parse *cmd_line, int cmds);
int		ft_dup2(int fdin, int fdout);
void	fdmulti_redef(t_parse *cmd, int *tmp_fdout, int *tmp_fdin, int cmds);
void	replace_fdmulti(t_data *data, t_parse *cmd);
void	replace_fd(t_data *data, t_parse *cmd);

/*exec_heredoc*/
int		handle_heredoc(t_data *data, t_parse *cmd_line);
void	heredoc_name(t_data *data, t_parse *cmd);
int		find_heredoc(t_data *data, t_parse *cmd, t_lexer *redir);
int		heredocfun(t_data *data, t_parse *cmd, char *delim);
int		cleanup_herefun(char **str, int *fd, int ret);

/*exec_cmdfinder*/
int		check_access(t_data *data, char *cmdname, char **cmdpath);
int		check_binary(t_data *data, char **cmdpath, char *cmdname);
int		cmdfinder(t_data *data, t_parse *cmd_line);
int		find_cmd(t_data *data, char *cmdname, char **cmdpath, char **paths);

/*exec_fds*/
int		handle_fds(t_parse *cmd);
int		handle_infile(t_parse *cmd, t_lexer *redir);
int		handle_outfile(t_parse *cmd_line, t_lexer *redir);

/*exec_fd_utils*/
int		cleanup_fd(int *fd);
int		update_fd(t_parse *cmd, char **name);
int		ft_open(char *file, t_type token, char *heredoc);
int		close_all_fds(t_parse *cmd_line);

/*exec_exstatus*/
void	ft_waitpid(t_data *data, t_parse *cmd);
void	check_status(int status, int *excode);

#endif