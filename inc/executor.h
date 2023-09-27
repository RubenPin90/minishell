#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

/*executor*/
int		executor(t_data *data);

/*exec_heredoc*/
void	handle_heredoc(t_data *data, t_parse *cmd_line);
int		find_heredoc(t_data *data, t_parse *cmd, t_lexer *redir);
int		heredocfun(t_data *data, t_parse *cmd, char *delim);

/*exec_cmdfinder*/
int		check_access(t_data *data, char *cmdname, char **cmdpath);
int		check_binary(t_data *data, char **cmdpath, char *cmdname);
int		cmdfinder(t_data *data, t_parse *cmd_line);
int		find_cmd(t_data *data, char *cmdname, char **cmdpath, char **paths);

/*exec_fds*/
int		handle_fds(t_data *data, t_parse *cmd);
int		handle_infile(t_data *data, t_parse *cmd, t_lexer *redir);
int		handle_outfile(t_data *data, t_parse *cmd_line, t_lexer *redir);

/*exec_fd_utils*/
int		cleanup_fd(int *fd);
int		update_fd(t_parse *cmd, char **name);
int		ft_open(char *file, t_type token, char *heredoc);
int		close_all_fds(t_parse *cmd_line);

#endif