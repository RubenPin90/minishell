/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapostol <aapostol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:35:33 by aapostol          #+#    #+#             */
/*   Updated: 2023/07/14 16:44:24 by aapostol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_lexer	*new_lexer_node(char *word, int token)
{
	t_lexer		*new;
	static int	i;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->word = word;
	new->token = token;
	new->i = i++;
	new->next = NULL;
	new->prev = NULL;
}

void	lexer_addback(t_lexer **lst, t_lexer *new)
{
	t_list	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
