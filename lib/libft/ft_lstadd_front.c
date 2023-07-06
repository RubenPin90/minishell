/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:24:18 by rpinchas          #+#    #+#             */
/*   Updated: 2022/10/24 10:49:28 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
int main(void)
{
	t_list *head;
	char	superman[] = "gWolf";
	char	batman[] = "ruben";
	head = ft_lstnew(superman);
	printf("%s\n", (char *)head->content);
	ft_lstadd_front(&head, ft_lstnew(batman));
	printf("%s\n", (char *)head->content);
}*/
