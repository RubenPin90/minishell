/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:53:52 by rpinchas          #+#    #+#             */
/*   Updated: 2022/10/15 18:13:38 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	dstlen;
	unsigned int	srclen;

	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	i = 0;
	if (dstlen >= size)
		return (srclen + size);
	while (src[i] && size - dstlen - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
		size--;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}
