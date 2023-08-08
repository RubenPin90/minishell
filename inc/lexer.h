#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

// lexer.c
void	lexer(char *input, t_lexer *lex);

// lexer_utils.c
t_lexer	*new_lexer_node(char *word, int token);
void	lexer_addback(t_lexer **lst, t_lexer *new);
void	free_lexer(t_lexer **lex);

#endif