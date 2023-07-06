/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourLogin <yourLogin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:11:48 by yourLogin         #+#    #+#             */
/*   Updated: 2022/10/17 14:35:33 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_outofstring(char *slice)
{
	slice = (char *)malloc(sizeof(char));
	if (!slice)
		return (NULL);
	*slice = '\0';
	return (slice);
}

char	*ft_substr(const char *string, unsigned int start, size_t len)
{
	char			*slice;
	unsigned int	i;
	unsigned int	s_len;

	if (!string)
		return (NULL);
	slice = 0;
	s_len = ft_strlen(string);
	if (start >= s_len)
		return (ft_outofstring(slice));
	if ((s_len - start) < len)
		len = s_len - start;
	slice = (char *)malloc((len + 1) * sizeof(char));
	if (!slice)
		return (NULL);
	i = 0;
	while (string[start + i] && i < len)
	{
		slice[i] = string[start + i];
		i++;
	}
	slice[i] = '\0';
	return (slice);
}

/*
int main()
{
	char	str[] = "Hallo wie geht's | BLUB ** | soll gefunden werden!";
	char	*ptr;
	int	start = 40;
	ptr = ft_substr(str, start, 7);
	printf("%s\n", ptr);
	free(ptr);
}
*/
