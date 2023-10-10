/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:44:29 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 13:59:04 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

/*lexer.c*/
int		lexer(t_data *data);
int		create_list(t_data *data, char **datainput);
char	*get_word(t_data *data, char *input, t_word *word);
void	fill_word(char *new, t_word *word);

/*lexer_utils.c*/
int		get_len(t_data *data, char *input, int *i, char quote);
int		unquoted_len(char *input, int *i);
int		quoted_len(char *input, int *i, char quote);
int		hard_cut(char c);
void	toggle_quotes(bool *ian, bool *other);

/*lexer_check_tokens.c*/
int		check_token(char *input);
int		check_double_redir(char *input, int i);
int		check_double_pipe(char *input, int i);
int		check_type(char *input, int *i);
void	skip_token(char *input, int *i);

/*lexer_check_quotes.c*/
int		check_quotes(char *str);
void	skip_quote(char *input, char quote, int *i);
void	skip_space(char *input, int *i);

/* lexer_list_utils.c*/
t_lexer	*add_node(t_data *data, char *input, t_word *word);
t_lexer	*new_lexer_node(char *word, int token);
void	lexer_addback(t_lexer **lst, t_lexer *new);
void	count_lexlst(t_lexer *lex);

#endif