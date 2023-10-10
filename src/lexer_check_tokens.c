/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:45:16 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 16:50:13 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_token(char *input)
{
	int	i;

	i = 0;
	skip_space(input, &i);
	if (input[i] == '|')
		return (error_msg(NULL, NULL, TOKEN_ERR, E_SYNERR));
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			skip_quote(input, input[i], &i);
		if (input[i] == '|')
			if (check_double_pipe(input, i))
				return (1);
		if (input[i] == '<' || input[i] == '>')
			if (check_double_redir(input, i))
				return (1);
		input++;
	}
	return (0);
}

int	check_double_redir(char *input, int i)
{
	static int	redir;

	i++;
	if (input[i] == '<' || input[i] == '>')
	{
		redir++;
		if (redir >= 2)
		{
			redir = 0;
			return (error_msg(NULL, NULL, TOKEN_ERR, E_SYNERR));
		}
		return (0);
	}
	redir = 0;
	while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
		i++;
	if (!input[i] || input[i] == '<' || input[i] == '>' || input[i] == '|')
		return (error_msg(NULL, NULL, TOKEN_ERR, E_SYNERR));
	return (SUCCESS);
}

int	check_double_pipe(char *input, int i)
{
	i++;
	while (input[i] == ' ')
		i++;
	if (!input[i] || input[i] == '|')
		return (error_msg(NULL, NULL, TOKEN_ERR, E_SYNERR));
	return (SUCCESS);
}

int	check_type(char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
		return (HEREDOC);
	else if (input[*i] == '<')
		return (INPUT);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		return (APPEND);
	else if (input[*i] == '>')
		return (OUTPUT);
	else if (input[*i] == '|')
		return (PIPE);
	else if (input[*i])
		return (WORD);
	return (STOP);
}

void	skip_token(char *input, int *i)
{
	while (input[*i] == '<' || input[*i] == '>')
		(*i)++;
}
