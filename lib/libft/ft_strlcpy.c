/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:53:52 by rpinchas          #+#    #+#             */
/*   Updated: 2022/10/12 13:42:01 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	long unsigned int	i;
	long unsigned int	cnt;

	i = 0;
	cnt = 0;
	if (size > 0)
	{
		while (src[cnt])
		{
			while ((i < size -1) && src[i])
			{
				dst[i] = src[i];
				i++;
			}
			cnt++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
