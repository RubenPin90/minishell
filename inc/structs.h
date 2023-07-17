#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

typedef struct s_data
{
	char			**envp;
	char			*input;
	struct s_lexer	*lex;
}	t_data;

typedef enum s_token
{
	PIPE = 1,
	OUTPUT,
	INPUT
}	t_token;

typedef struct s_lexer
{
	char			*word;
	t_token			token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

#endif