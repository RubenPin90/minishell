/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:04:33 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 15:04:34 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_export(t_data *data, t_parse *cmd)
{
	int			num_args;
	bool		equal;
	int			i;
	int			err;

	num_args = ft_arrlen(cmd->cmd);
	if (num_args == 1)
		ft_bubsort(data->env_arr, data->env);
	i = 0;
	while (cmd->cmd[++i])
	{
		equal = false;
		err = check_valid(cmd->cmd[i], &equal);
		if (err)
			return (export_error(err, cmd->cmd[i]));
		if (equal == true)
			if (update_env(data->env, cmd->cmd[i]))
				ft_parent_error(MALLOC_ERR, data, cmd);
		if (equal == false)
		{
			if (check_exp_lst(data->exp_lst, data->env, cmd->cmd[i]))
				ft_parent_error(MALLOC_ERR, data, cmd);
		}
	}
	return (SUCCESS);
}

int	check_valid(char *arg, bool *equal)
{
	int		i;

	i = 0;
	if (arg[i] && (ft_isalpha(arg[i]) || arg[i] == '_'))
		i++;
	else if (arg[i] && arg[i] == '-')
		return (AGAIN);
	else
		return (FAIL);
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (arg[i] && arg[i] == '=')
		*equal = true;
	else if (arg[i] && !(ft_isalnum(arg[i]) || arg[i] == '_'))
		return (FAIL);
	return (SUCCESS);
}

int	check_exp_lst(t_lexer *exp_lst, t_lstenv *env, char *arg)
{
	int	len;

	if (!exp_lst)
		return (SUCCESS);
	while (exp_lst->next)
		exp_lst = exp_lst->next;
	while (exp_lst)
	{
		len = ft_keylen(exp_lst->word);
		if (!ft_strncmp(arg, exp_lst->word, len))
		{
			if (update_env(env, exp_lst->word) == FAIL)
				return (FAIL);
			break ;
		}
		exp_lst = exp_lst->prev;
	}
	return (SUCCESS);
}

void	export_check(t_data *data, t_lexer *lex)
{
	bool	equals;
	bool	first;

	equals = false;
	while (lex)
	{
		first = false;
		if (lex->token == WORD && ft_strchr(lex->word, '=') && \
							(!lex->prev || lex->prev->token == PIPE))
		{
			if (!check_valid(lex->word, &equals) || equals == true)
			{
				first = ft_push_redir(&lex, &data->exp_lst, first);
				if (!lex || first == true || !lex->next)
					data->lex = lex;
				else
					lex = lex->next;
			}
			else
				lex = lex->next;
		}
		else
			lex = lex->next;
	}
}

int	export_error(int err, char *cmd)
{
	if (err == 1)
		return (error_msg("export", cmd, INV_IDENT_ERR, E_ERROR));
	else
		return (error_msg("export", "-", INV_OPT_ERR, E_SYNERR));
}
