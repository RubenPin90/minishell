#include "builtin.h"

int	check_valid(char *arg, bool *equal)
{
	int		i;

	i = 0;
	if (arg && ft_isalpha(arg[i]))
		i++;
	else
		return (FAIL);
	while (arg && ft_isalnum(arg[i]))
		i++;
	if (arg && arg[i] == '=')
		*equal = true;
	return (SUCCESS);
}

int	update_env(t_lstenv *env, char *arg)
{
	t_lstenv	*exp_arg;
	int			ret;

	ret = 0;
	exp_arg = lstenv_create(arg);
	if (!exp_arg)
		return (FAIL);
	ret = update_path(env, exp_arg->value, exp_arg->key);
	lstenv_clear(&exp_arg);
	if (ret == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int ft_keylen(char *str)
{
	int i;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	return (i);
}

int	check_exp_lst(t_lexer *exp_lst, t_lstenv *env, char *arg)
{
	int len;

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

int	ft_export(t_data *data, t_parse *cmd)
{
	int			num_args;
	bool		equal;
	int			i;

	num_args = ft_arrlen(cmd->cmd);
	if (num_args == 1)
		ft_bubsort(data->env_arr, data->env);
	i = 1;
	while (cmd->cmd[i])	
	{
		equal = false;
		if (check_valid(cmd->cmd[i], &equal))
			return (error_msg("export", "not a valid identifier"));
		if (equal == true)
			if (update_env(data->env, cmd->cmd[i]))
				ft_error(MALLOC_ERR, data);
		if (equal == false)
		{
			if (check_exp_lst(data->exp_lst, data->env, cmd->cmd[i]))
				ft_error(MALLOC_ERR, data);	
		}
		i++;
	}
	return (SUCCESS);
}

void	ft_bubsort(char **ar, t_lstenv *env)
{
	int		len;
	int		i;
	char	*tmp;

	len = env_len(env);
	while (len-- > 1)
	{
		i = 0;
		while (ar[i] && ar[i + 1])
		{
			if (ft_strncmp(ar[i], ar[i + 1], ft_strlen(ar[i + 1])) > 0)
			{
				tmp = ar[i + 1];
				ar[i + 1] = ar[i];
				ar[i] = tmp;
			}
			i++;
		}
	}
	print_env_arr(ar);
}


void	export_check(t_data *data, t_lexer *lex)
{
	bool	equals;
	bool	first;

	equals = false;
	while(lex)
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
