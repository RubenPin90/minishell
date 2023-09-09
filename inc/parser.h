#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

/*parser*/
bool	ft_push_redir(t_lexer **a, t_lexer **b, bool check);
int		init_cmd(t_lexer *cmd_list, t_parse *current_cmd);
int		extract_cmd(t_data *data, t_lexer **lst, t_parse *cmd_line, char **cmd);
int		parser(t_data *data, t_lexer *lst);

/*parser_utils*/
int		tkn_counter(t_lexer *lex, t_type tkn, t_type end);
t_parse *free_parser(t_parse *cmd_line);

#endif