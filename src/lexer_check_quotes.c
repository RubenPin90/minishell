/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:45:23 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 13:45:24 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_quotes(char *str)
{
	int		i;
	bool	doubles;
	bool	singles;

	i = 0;
	doubles = false;
	singles = false;
	while (str[i])
	{
		if (str[i] == '"')
			toggle_quotes(&doubles, &singles);
		if (str[i] == '\'')
			toggle_quotes(&singles, &doubles);
		i++;
	}
	if (doubles == true || singles == true)
		return (1);
	return (0);
}

void	skip_quote(char *input, char quote, int *i)
{
	(*i)++;
	while (input[*i] != quote)
		(*i)++;
}

void	skip_space(char *input, int *i)
{
	while (input[*i] == ' ' || (input[*i] >= 9 && input[*i] <= 13))
		(*i)++;
}
