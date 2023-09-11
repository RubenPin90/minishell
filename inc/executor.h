#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

/*executor*/
int executor(t_data *data);


/*exec_fds*/
int		handle_fds(t_data *data, t_parse *cmd);
int		handle_infile(t_data *data, t_parse *cmd, t_lexer *redir);
int		handle_outfile(t_data *data, t_parse *cmd_line, t_lexer *redir);

	/*exec_heredoc*/
void	handle_heredoc(t_data *data, t_parse *cmd_line);
int		find_heredoc(t_data *data, t_parse *cmd, t_lexer *redir);
int		heredocfun(t_parse *cmd, char *delim);

#endif