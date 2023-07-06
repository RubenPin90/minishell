/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:53:52 by rpinchas          #+#    #+#             */
/*   Updated: 2022/10/15 21:39:38 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*sn1;
	const unsigned char	*sn2;

	i = 0;
	sn1 = s1;
	sn2 = s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (sn1[i] != sn2[i])
			return (sn1[i] - sn2[i]);
		i++;
	}
	return (0);
}
