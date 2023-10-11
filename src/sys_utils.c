/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:37:44 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/11 16:16:59 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_wrapper(char *str1, char*str2, char *str3)
{
	char	*tmp;
	char	*strnew;

	strnew = ft_strjoin(str1, str2);
	if (!strnew)
		return (NULL);
	tmp = strnew;
	strnew = ft_strjoin(strnew, str3);
	if (!strnew)
	{
		tmp = free_null(tmp);
		return (NULL);
	}
	tmp = free_null(tmp);
	return (strnew);
}

char	**arr_expand(char **arr, char *str)
{
	int		i;
	int		arrlen;
	char	**new_arr;

	if (!arr && !str)
		return (NULL);
	arrlen = 0;
	if (arr)
		arrlen = ft_arrlen(arr);
	new_arr = ft_calloc(arrlen + 1, sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = -1;
	while (++i < arrlen)
		new_arr[i] = arr[i];
	new_arr[i] = ft_strdup(str);
	if (!new_arr[i])
		new_arr = free_arr(new_arr);
	arr = free_arr(arr);
	return (new_arr);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

int	is_executable(t_parse *cmdl)
{
	if (cmdl->execute == false)
		return (FAIL);
	if (!cmdl->cmd || !cmdl->cmd[0])
	{
		cmdl->exstatus = E_SUCCESS;
		return (FAIL);
	}
	return (SUCCESS);
}

int	tkn_counter(t_lexer *lex, t_type tkn, t_type end)
{
	int	count;

	count = 0;
	while (lex && lex->token != end)
	{
		if (lex->token == tkn)
			count++;
		lex = lex->next;
	}
	return (count);
}
