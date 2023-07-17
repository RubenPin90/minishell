#include "../inc/minishell.h"

// create a new list node for lexer struct
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
	return (new);
}

// add list node to the back of linked lexer list
void	lexer_addback(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

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
