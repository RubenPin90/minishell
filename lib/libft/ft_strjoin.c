/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourLogin <yourLogin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:18:11 by yourLogin         #+#    #+#             */
/*   Updated: 2022/10/17 19:56:49 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		slen;

	if (!s1 || !s2)
		return (NULL);
	slen = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = (char *)malloc(slen * sizeof(char));
	if (s3 == NULL)
		return (0);
	ft_strlcpy(s3, s1, slen);
	ft_strlcat(s3, s2, slen);
	return (s3);
}
/*
int main()
{
	char	str[] = "Hallo, ";
	char	str2[] = "Adrienn";
	char	*str3;
	str3 = ft_strjoin(str, str2);
	printf("str1: %s  |str2: %s\n", str, str2);
	printf("str3: %s\n", str3);
	free(str3);
	return (0);
}
*/
