#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

// lexer.c
int		lexer(t_data *data);
t_lexer	*create_list(t_data *data, char **datainput);
char	*get_word(t_data *data, char *input, t_word *word);
void	fill_word(char *new, t_word *word);

// lexer_utils.c
int		get_len(t_data *data, char *input, int *i, char quote);
int		unquoted_len(char *input, int *i);
int		quoted_len(char *input, int *i, char quote);
void	skip_space(char *input, int *i);
int		hard_cut(char c);

// lexer_checks.c
int		check_quotes(t_data *data, char *str);
int		check_token(char *input);
int		check_redir(char *input);
int		check_pipe(char *input);
int		check_type(char *input, int *i);

// lexer_list_utils.c
t_lexer	*add_node(t_data *data, char *input, t_word *word);
t_lexer	*new_lexer_node(char *word, int token);
void	lexer_addback(t_lexer **lst, t_lexer *new);
void	count_lexlst(t_lexer *lex);
void	free_lexer(t_lexer **lex);

#endif