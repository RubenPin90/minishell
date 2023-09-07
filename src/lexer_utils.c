#include "../inc/lexer.h"

char	*get_word(t_data *data, char *input, t_word *word)
{
	// char	*tmp;
	int		i;

	i = word->i;
	word->start = i;
	word->quoted = false;
	while (input[i] && input[i] != ' ' && input[i] != '>' && \
			input[i] != '<' && input[i] != '|')
	{
		if (input[i] == '$')
		{
			// tmp = input;
			input = expander(input, &i);
			// printf("get_word, input[i] == '$': %s\n", input);
			// free (tmp);
		}
		if (input[i] == '"' || input[i] == '\'')
		{
			input = get_quote(data, input, &i, input[i]);
			word->start++;
			word->quoted = true;
		}
		i++;
	}
	word->len = i - word->start - word->quoted;
	word->i = i;
	return (input);
}

char	*get_quote(t_data *data, char *input, int *i, char quote)
{
	// char 	*tmp;

	(void)data;
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		if (input[*i] == '$' && quote == '"')
		{
			// tmp = input;
			input = expander(input, i);
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

void count_lexlst(t_lexer *lex)
{
	t_lexer *tmp;
	int		i;

	i = 0;
	tmp = lex;
	while (tmp)
	{
		tmp->i = i;
		tmp = tmp->next;
		i++;
	}
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
		(*lst)->next = NULL;
		(*lst)->prev = NULL;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
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
