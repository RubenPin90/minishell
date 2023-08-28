#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

/*parser*/
int	handle_redir(t_data *data, t_type token, t_parse *cmd_line, char *word);
int	parser(t_data *data);
int	init_cmd(t_lexer *cmd_list, t_parse *current_cmd);
int	extract_cmd(t_data *data, t_lexer **lst, t_parse *cmd_line, char **cmd);

/*parser_utils*/
int tkn_counter(t_lexer *lex, t_type tkn, t_type end);
int	handle_infile(t_parse *cmd_line, char *word);
int	handle_heredoc(t_parse *cmd_line, char *word);
int	handle_outfile(t_parse *cmd_line, char *word, int typ);
t_parse *free_parser(t_parse *cmd_line);

#endif