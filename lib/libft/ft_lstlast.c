/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:27:12 by rpinchas          #+#    #+#             */
/*   Updated: 2022/11/19 19:06:20 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
/*
int main()
{
	t_list	*irgendwie = NULL;
	char	name[] = "Ruben";
	char	name2[] = "Gabriel";
	
	//irgendwie = ft_lstnew(name);
	ft_lstadd_back(&irgendwie, ft_lstnew(name));
	ft_lstadd_back(&irgendwie, ft_lstnew(name2));
	printf("%d\n", ft_lstsize(irgendwie));
	ft_lstlast(irgendwie);
	//printf("%s\n", (char *)ft_lstlast(irgendwie)->content);
	printf("%s\n", (char *)irgendwie->content);
	printf("%s\n", (char *)irgendwie_neu->content);
	return (0);
}


*/
