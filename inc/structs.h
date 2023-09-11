#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

typedef struct s_data t_data;
typedef int (*bltn)(t_data *data);

typedef enum s_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
	EMPTY
}	t_type;

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
	t_type			token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_word
{
	char	*str;
	int		start;
	int		len;
	int		type;
	int		i;
	// bool	quoted;
}	t_word;

/**
 * @brief Grouping lexer input list together into cmds.
 * 
 */
typedef struct s_parse
{
	int				id;
	char			*cmd_path;
	char			**cmd;
	bltn			func;
	bool			parent;
	t_lexer			*redir;
	char			*infile;
	char			*outfile;
	int				fd_in;
	int				fd_out;
	pid_t			pid;
	int				fd_pipes[2];
}	t_parse;

typedef struct s_data
{
	t_lstenv		*env;
	char			**env_arr;
	char			*input;
	int				cmds;
	char			**paths;
	struct s_parse	*cmd_line;
	struct s_lexer	*lex;
	struct s_word	*word;
}	t_data;

#endif