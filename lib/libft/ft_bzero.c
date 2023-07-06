/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:53:51 by rpinchas          #+#    #+#             */
/*   Updated: 2022/10/11 17:34:12 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char				*tmp;
	long unsigned int	i;

	tmp = (char *)s;
	i = 0;
	while (i < n)
	{
		tmp[i] = 0;
		i++;
	}
}
/*int main ()
  {
  char str[] = "Hallo, Wie gehts?";
  char str2[] = "Hallo, Wie gehts?";
  ft_bzero(str, 3);
  bzero(str2, 3);
  printf("%s\n", str);
  printf("%s\n", str2);
  }*/
