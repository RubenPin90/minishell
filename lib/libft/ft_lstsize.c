/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:25:52 by rpinchas          #+#    #+#             */
/*   Updated: 2022/10/24 10:51:03 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
/*
int main()
{
	t_list	*head;
	char	name[] = "Ruben";
	char	name2[] = "Gabriel";

	head = ft_lstnew(name);
	ft_lstadd_front(&head, ft_lstnew(name2));
	printf("%d\n", ft_lstsize(head));
	return (0);
}
*/
