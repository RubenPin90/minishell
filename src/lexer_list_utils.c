#include "../inc/lexer.h"

/**
 * @brief Add a new node to the end of the list
 * 
 * Copies a word from the input string into 
 * @param data 
 * @param start 
 * @param len 
 * @param type 
 */
t_lexer	*add_node(t_data *data, char *lst_word, t_word *word)
{
	t_lexer	*node;

	if (word->type == PIPE)
		word->len = 1;
	if (!lst_word)
		node = new_lexer_node(NULL, EMPTY);
	else
		node = new_lexer_node(ft_strdup(lst_word), word->type);
	// printf("node->word: %s\n", node->word);
	if (!node || !node->word)
		return (NULL);
	lexer_addback(&data->lex, node);
	return (node);
}


// create a new list node for lexer struct
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

// add list node to the back of linked lexer list
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

/**
 * @brief Destroying & freeing the lexer struct.
 * 
 * Checks if lex exists, if yes loops through the list
 * and frees + sets every node to NULL. 
 */
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
