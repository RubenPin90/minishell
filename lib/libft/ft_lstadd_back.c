/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:28:02 by rpinchas          #+#    #+#             */
/*   Updated: 2023/02/06 16:43:34 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
}
/*
int main()
{
	t_list	*head = NULL;
	char	name[] = "Ruben";
	char	name2[] = "Gabriel";
	char	name3[] = "Annie";

	//head = ft_lstnew(name);
	ft_lstadd_back(&head, ft_lstnew(name));
	ft_lstadd_back(&head, ft_lstnew(name2));
	printf("%d\n", ft_lstsize(head));
	printf("%s\n", (char *)head->content);
	printf("%s\n", (char *)ft_lstlast(head)->content);
	ft_lstadd_back(&head, ft_lstnew(name3));
	printf("%s\n", (char *)ft_lstlast(head)->content);
	return (0);
}

	//ft_lstlast(*lst)->next = new;

*/
