#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

/*parser*/
int	parser(t_data *data);
void	extract_cmd(t_data *data, t_lexer **lst, int *cmd_id);

/*parser_utils*/
int tkn_counter(t_lexer *lex, t_token tkn);
int	handle_redir(t_lexer **lex, int eoc, t_parse *cmd);
int	handle_heredoc(t_lexer **lex, int eoc, t_parse *cmd);
int	handle_cmd(t_lexer **lex, int eoc, t_parse *cmd);

#endif