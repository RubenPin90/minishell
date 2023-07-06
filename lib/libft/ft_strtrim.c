/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourLogin <yourLogin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:27:42 by yourLogin         #+#    #+#             */
/*   Updated: 2022/10/17 19:56:03 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[j] && ft_strrchr(set, s1[j]))
		j--;
	return (ft_substr(s1, i, j - i + 1));
}
/*
int main()
{
	char	str[] = "taathallo ich heiße thomas und bin 1740 geb.ttat";	
	char	set[] = "at";
	char	*ptr;
	ptr = ft_strtrim(str, set);
	printf("str: %s\n set: %s\n Ergebnis: %s\n", str, set, ptr);
	free(ptr);
	return (0);
}
*/
