/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubsky <rubsky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:18:56 by rubsky            #+#    #+#             */
/*   Updated: 2023/07/06 16:53:25 by rubsky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Copy the environment pointer into the struct*/
char	**copy_envp(char **env_org)
{
	int		len;
	int		i;
	char	**tmp;

	len = 0;
	while (env_org[len])
		len++;
	tmp = (char **)ft_calloc(sizeof(char *), len + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tmp[i] = ft_strdup(env_org[i]);
		i++;
	}
	return (tmp);
}
