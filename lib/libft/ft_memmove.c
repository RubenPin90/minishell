/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:53:52 by rpinchas          #+#    #+#             */
/*   Updated: 2022/10/12 14:10:18 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	long unsigned int	i;
	char				*ndest;
	const char			*nsrc;

	ndest = dest;
	nsrc = src;
	i = 0;
	if (!dest && !src)
		return (0);
	if (dest < src)
	{
		while (i < n)
		{
			ndest[i] = nsrc[i];
			i++;
		}
	}
	else
	{
		i = n;
		while ((int)--i >= 0)
			ndest[i] = nsrc[i];
	}
	return (ndest);
}
