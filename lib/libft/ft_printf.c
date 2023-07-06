/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 09:44:45 by rpinchas          #+#    #+#             */
/*   Updated: 2022/11/18 12:59:49 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countnbr(unsigned long d, char c, int base)
{
	int	i;

	i = 1;
	ft_putnbr_base(d, c, base);
	while ((d / base) != 0)
	{
		d = d / base;
		i++;
	}
	return (i);
}

void	ft_putnbr_base(unsigned long long x, char c, int base)
{
	if ((int)x >= base)
	{
		ft_putnbr_base((x / base), c, base);
		x = x % base;
	}
	if (x < 10)
		ft_printchar(x + '0');
	else
	{
		if (c == 'x' || c == 'p')
			ft_printchar('a' + x - 10);
		else
			ft_printchar('A' + x - 10);
	}
}

int	ft_checkformat(va_list arg, char c)
{
	if (c == 'c')
		return (ft_printchar(va_arg(arg, int)));
	else if (c == 's')
		return (ft_printstr(va_arg(arg, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_printint(va_arg(arg, int), c));
	else if (c == 'p')
		return (ft_printp(va_arg(arg, unsigned long long), c));
	else if (c == 'u')
		return (ft_countnbr(va_arg(arg, unsigned int), c, 10));
	else if (c == 'x' || c == 'X')
		return (ft_countnbr(va_arg(arg, unsigned int), c, 16));
	else if (c == '%')
		return (write(1, "%", 1));
	else
	{
		write(1, "%", 1);
		write(1, &c, 1);
		return (2);
	}
}

int	ft_check(va_list arg, const char *c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (c[i])
	{
		if (c[i] == '%' && c[i + 1] != '\0')
		{
			i++;
			count += ft_checkformat(arg, c[i]);
		}
		else
			count += write(1, &c[i], 1);
		if (c[i])
			i++;
	}
	return (count);
}

int	ft_printf(const char *c, ...)
{
	va_list	arg;
	int		counter;

	counter = 0;
	va_start(arg, c);
	counter = ft_check(arg, c);
	va_end(arg);
	return (counter);
}
