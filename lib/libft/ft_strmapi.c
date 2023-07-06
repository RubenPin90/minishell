/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:32:27 by rpinchas          #+#    #+#             */
/*   Updated: 2022/10/19 15:44:53 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*new;

	if (!s)
		return (NULL);
	new = ft_strdup(s);
	if (!new)
		return (NULL);
	i = 0;
	while (new[i])
	{
		new[i] = f(i, new[i]);
		i++;
	}
	return (new);
}
