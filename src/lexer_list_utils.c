/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:45:38 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/12 13:58:01 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*add_node(t_data *data, char *lst_word, t_word *word)
{
	t_lexer	*node;

	if (word->type == PIPE)
		word->len = 1;
	if (!lst_word)
		node = new_lexer_node(ft_strdup(""), EMPTY, data->exp_equal);
	else
		node = new_lexer_node(ft_strdup(lst_word), word->type, data->exp_equal);
	if (!node)
		ft_error(MALLOC_ERR, data);
	data->exp_equal = false;
	lexer_addback(&data->lex, node);
	return (node);
}

t_lexer	*new_lexer_node(char *word, int token, bool exp_equal)
{
	t_lexer		*new;

	if (!word)
		return (NULL);
	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->word = word;
	new->token = token;
	new->qu_equal = exp_equal;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	lexer_addback(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		new->prev = NULL;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	new->prev = tmp;
}

void	count_lexlst(t_lexer *lex)
{
	int		i;

	i = 0;
	while (lex)
	{
		lex->i = i;
		lex = lex->next;
		i++;
	}
}
