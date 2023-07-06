/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:31:50 by rpinchas          #+#    #+#             */
/*   Updated: 2022/11/10 13:00:05 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_bzero_sp(int n)
{
	char	*tmp;

	n++;
	tmp = (char *) malloc (sizeof(char) * 2);
	if (!tmp)
		return (NULL);
	tmp[0] = '0';
	tmp[1] = '\0';
	return (tmp);
}

static void	ft_putnbr(long n, char *s, int digit, int minus)
{
	if (minus == 2)
	{
		s[0] = '-';
		minus = 0;
		digit += 1;
	}
	digit--;
	if (n > 9)
	{
		ft_putnbr(n / 10, s, digit, minus);
		n = n % 10;
	}
	s[digit] = (n + '0');
}

char	*ft_itoa(int n)
{
	char	*str;
	int		digit;
	int		minus;
	long	n_new;

	n_new = (long)n;
	if (n == 0)
		return (ft_bzero_sp(n));
	digit = ft_digit(n_new);
	minus = 1;
	if (n < 0)
	{
		minus++;
		n_new *= -1;
	}
	str = (char *) ft_calloc (sizeof(char), digit + minus);
	if (!str)
		return (NULL);
	ft_putnbr(n_new, str, digit, minus);
	return (str);
}
/*
int main()
{
	int		num = -5859;
	int		num2 = 1000034;
	char	*str;
	char	*str2;

	str = ft_itoa(num);
	str2 = ft_itoa(num2);
	printf("str: %s str2: %s\n", str, str2);
	free (str);
	return (0);
}
*/
