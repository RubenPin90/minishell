#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

/*parser*/
int	parser(t_data *data, t_lexer *lex, t_parse **cmd_line);
int	extract_cmd(t_lexer **lst_head, int eoc, t_parse *cmd);

/*parser_utils*/
int tkn_counter(t_lexer *lex, t_type tkn);
int	handle_redir(t_lexer **lex, int eoc, t_parse *cmd);
int	handle_heredoc(t_lexer **lex, int eoc, t_parse *cmd);
int	handle_cmd(t_lexer **lex, int eoc, t_parse *cmd);

#endif