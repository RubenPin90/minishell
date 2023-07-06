/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:30:57 by rpinchas          #+#    #+#             */
/*   Updated: 2022/10/24 17:15:09 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			word++;
		while (s[i] != c && s[i])
			i++;
	}
	return (word);
}

static char	**ft_putword(char **arr, char c, const char *s, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
		{
			j++;
			i++;
		}
		if (j != 0)
		{
			i = i - j;
			arr[k] = ft_substr(s, i, j);
			if (!arr[k])
				return (NULL);
			k++;
			i = i + j - 1;
		}
		j = 0;
		i++;
	}
	return (arr);
}

static void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		word;
	char	**array;

	if (!s)
		return (NULL);
	word = ft_wordcount((char *)s, c);
	array = (char **) malloc (sizeof(char *) * (word + 1));
	if (!array)
	{
		free(array);
		return (NULL);
	}
	if (!ft_putword(array, c, s, 0))
	{
		free_array(array);
		return (NULL);
	}
	array[word] = NULL;
	return (array);
}
/*
int main()
{
	char	str[] = "tripounalle";
	char	sep = 0;
	char	**ptr;
	int		i;

	i = 0;
	ptr = ft_split(str, sep);
	while (ptr[i])
	{
		printf("%s\n", ptr[i]);
		i++;
	}
	free(ptr);
	return(0);
}
*/
