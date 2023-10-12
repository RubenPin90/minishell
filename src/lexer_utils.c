/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:45:07 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/12 14:05:19 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	get_len(t_data *data, char *input, int *i, char quote)
{
	int		len;

	if (input[*i] == '"' || input[*i] == '\'')
	{
		data->exp_equal = true;
		if (data->word->type == HEREDOC)
			data->word->type = Q_HEREDOC;
		len = quoted_len(input, i, quote);
		data->word->start++;
		data->word->quoted = true;
	}
	else
		len = unquoted_len(input, i);
	return (len);
}

int	unquoted_len(char *input, int *i)
{
	int	len;

	len = 0;
	while (!hard_cut(input[*i]) && input[*i] != '"' && input[*i] != '\'')
	{
		len++;
		(*i)++;
	}
	return (len);
}

int	quoted_len(char *input, int *i, char quote)
{
	int		len;

	len = 0;
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		len++;
		(*i)++;
	}
	return (len);
}

int	hard_cut(char c)
{
	if (!c || c == '<' || c == '>' || c == '|' || c == ' ' || \
		(c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	toggle_quotes(bool *ian, bool *other)
{
	if (*ian == false && *other == false)
		*ian = true;
	else
		*ian = false;
}
