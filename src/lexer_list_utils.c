#include "../inc/lexer.h"

t_lexer	*add_node(t_data *data, char *lst_word, t_word *word)
{
	t_lexer	*node;

	if (word->type == PIPE)
		word->len = 1;
	if (!lst_word)
	{
		printf("EMPTY\n");
		node = new_lexer_node(NULL, EMPTY);
	}
	else
		node = new_lexer_node(ft_strdup(lst_word), word->type);
	if (!node || !node->word)
		return (NULL);
	lexer_addback(&data->lex, node);
	return (node);
}

t_lexer	*new_lexer_node(char *word, int token)
{
	t_lexer		*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->word = word;
	new->token = token;
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

void	free_lexer(t_lexer **lex)
{
	t_lexer	*tmp;

	tmp = *lex;
	while (*lex)
	{
		tmp = (*lex)->next;
		if ((*lex)->word)
			free((*lex)->word);
		free(*lex);
		*lex = tmp;
	}
	*lex = NULL;
}
