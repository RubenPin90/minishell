/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:53:52 by rpinchas          #+#    #+#             */
/*   Updated: 2022/10/20 12:26:48 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)s;
	while (s[i] != (char)c && s[i] != '\0')
	{
		i++;
		ptr++;
	}
	if (s[i] == (char)c)
		return (ptr);
	else
		return (0);
}
/*
int main()
{
	char s[] = "tripouille";
	char *i;
	char *j;

	i = strchr(s, 't' + 256);
	j = ft_strchr(s, 't' + 256);
	printf("original: %s\n meins: %s\n", i, j);
	return (0);
}*/
