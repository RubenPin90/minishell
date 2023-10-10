/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:02:28 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 14:03:15 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "minishell.h"

/*expander.c*/
char	*expander(t_data *data, char *input);
void	expander_prep(t_data *data, char *input, int *i);
char	*expander_time(t_data *data, char *input, int i);
char	*expand_input(char *input, int index, char *value, int var_len);

/*expander_tokens.c*/
int		is_token(char c);
int		check_for_tokens(char *val);
char	*add_quotes_to_tokens(char *val, int count);

/*expander_utils.c*/
int		get_var_len(char *input, int i);
char	*get_value(t_data *data, char *input, int start, int len);
void	skip_delim(char *input, int *i);
int		is_quoted_dollarsign(t_data *data, char *input, int i);
bool	toggle_bool(bool ian);

#endif