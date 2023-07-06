/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:53:51 by rpinchas          #+#    #+#             */
/*   Updated: 2022/11/21 17:28:51 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*p;
	unsigned long	len;

	len = nmemb * size;
	p = (void *)malloc(len);
	if (p == NULL || len > 2147483647)
		return (0);
	ft_bzero(p, len);
	return (p);
}
