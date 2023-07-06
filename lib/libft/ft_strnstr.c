/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:53:52 by rpinchas          #+#    #+#             */
/*   Updated: 2022/10/24 17:15:53 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	litn;

	if (!big && len == 0)
		return (0);
	litn = *little;
	if (!litn)
		return ((char *)big);
	j = ft_strlen(little);
	i = 0;
	while (*big && j <= len--)
	{
		while (*big == litn)
		{
			i++;
			if (i == j)
				return ((char *)big);
			if (little[i] != big[i])
				break ;
		}
		i = 0;
		big++;
	}
	return (0);
}
