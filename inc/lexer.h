#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

// lexer.c
int		lexer(t_data *data);
t_lexer	*create_list(t_data *data, char *input);
void	add_node(t_data *data, int start, int len, int type);

// lexer_utils.c
t_lexer	*new_lexer_node(char *word, int token);
void	lexer_addback(t_lexer **lst, t_lexer *new);
void	free_lexer(t_lexer **lex);
void	skip_space(char *input, int *i);
void	get_quote(char *input, int *i, char quote);
void	get_word(char *input, int *i);

// lexer_checks.c
int		check_quotes(char *str);
int		check_token(char *input);
int		check_redir(char *input);
int		check_pipe(char *input);
int		check_type(char *input, int *i);

#endif