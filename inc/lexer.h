#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

// lexer.c
int	lexer(char *input, t_lexer *lex);
int	check_token(char *input);
t_lexer	*create_list(char *input, t_lexer *lex);

// lexer_utils.c
t_lexer	*new_lexer_node(char *word, int token);
void	lexer_addback(t_lexer **lst, t_lexer *new);

#endif