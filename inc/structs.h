#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

typedef enum s_token
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
}	t_token;

typedef struct s_lstenv
{
	char			*key;
	char			*value;
	struct s_lstenv	*next;
	struct s_lstenv	*prev;
}	t_lstenv;

typedef struct s_lexer
{
	char			*word;
	t_token			token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

/**
 * @brief Grouping lexer input list together into cmds.
 * 
 */
typedef struct s_parse
{
	char			*cmd_link;
	char			**cmd;
	char			*infile;
	char			*outfile;
	char			*heredoc;
	int				num_redir;
}	t_parse;

typedef struct s_data
{
	t_lstenv		*env;
	char			*input;
	int				cmds;
	struct s_parse	*cmd_line;
	struct s_lexer	*lex;
}	t_data;

#endif