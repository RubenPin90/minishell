/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:53:18 by rpinchas          #+#    #+#             */
/*   Updated: 2022/10/24 17:43:36 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_overflow(const char *nptr, long long num, int sign)
{
	long long	newn;

	newn = num * 10 + (*nptr - 48);
	if (newn < num)
	{
		if (sign == 1)
			return (-1);
		else
			return (0);
	}
	return (2);
}

int	ft_atoi(const char *nptr)
{
	long long	res;
	int			check;
	int			sign;

	res = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		check = ft_overflow((const char *)nptr, res, sign);
		if (check == 2)
			res = res * 10 + (*nptr - 48);
		else
			return (check);
		nptr++;
	}
	return ((int)res * sign);
}
/*
int main()
{
	char	str[] = "9223372036854775809";
	
	printf("%d\n", ft_atoi(str));
	printf("%d\n", atoi(str));
}
*/
