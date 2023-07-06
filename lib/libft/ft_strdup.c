/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:53:52 by rpinchas          #+#    #+#             */
/*   Updated: 2022/10/24 17:42:25 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	slen;

	slen = ft_strlen(s) + 1;
	ptr = (char *)malloc(slen * sizeof(char));
	if (ptr == NULL)
		return (0);
	ft_strlcpy(ptr, s, slen);
	return (ptr);
}
/*
int main()
{
	char	ptr[] = "Hallo";
	char	*cpy;
	cpy = ft_strdup(ptr);
	printf("ptr: |%s| was copied into -->cpy: %s", ptr, cpy);
}
*/
