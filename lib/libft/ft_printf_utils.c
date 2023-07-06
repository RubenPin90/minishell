/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:43:55 by rpinchas          #+#    #+#             */
/*   Updated: 2022/11/18 13:57:17 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
		i += ft_printchar(str[i]);
	return (i);
}

int	ft_printint(long d, char c)
{
	int	i;
	int	base;

	i = 0;
	base = 10;
	if (d < 0)
	{
		d *= -1;
		ft_printchar('-');
		i++;
	}
	i += ft_countnbr(d, c, base);
	return (i);
}

int	ft_printp(unsigned long long p, char c)
{
	int	i;
	int	base;

	i = 0;
	base = 16;
	if (!p)
		return (ft_printstr("(nil)"));
	i += ft_printstr("0x");
	i += ft_countnbr(p, c, base);
	return (i);
}
