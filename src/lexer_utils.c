#include "../inc/lexer.h"

char	*get_word(t_data *data, char *input, t_word *word)
{
	char	*tmp;
	int		i;

	i = word->i;
	word->start = i;
	word->quoted = false;
	while (input[i] && input[i] != ' ' && input[i] != '>' && \
			input[i] != '<' && input[i] != '|')
	{
		if (input[i] == '$')
		{
			tmp = input;
			input = expander(input, &i);
			printf("get_word, input[i] == '$': %s\n", input);
			// printf("get_word, input[i] == '$': %s\n", input);
			// free (tmp);
		}
		if (input[i] == '"' || input[i] == '\'')
		char	*get_quote(t_data *data, char *input, int *i, char quote)
		{
			tmp = input;
			input = expander(input, i);
			printf("%s\n", input);
			// printf("%s\n", input);
			// free(tmp);
		}
		(*i)++;
	}
	return (input);
}

void	skip_space(char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
}

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
