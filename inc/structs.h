#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

typedef struct s_lstenv
{
	char 			*key;
	char 			*value;
	struct s_lstenv *next;
	struct s_lstenv *prev;
}	t_lstenv;

typedef struct s_data
{
	t_lstenv		*env;
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