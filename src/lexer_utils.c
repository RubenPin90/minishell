#include "../inc/lexer.h"

char	*get_word(t_data *data, char *input, t_word *word)
{
	char	*unquoted;
	char	*tmp;
	int		i;

	i = word->i;
	word->start = i;
	while (input[i] && input[i] != ' ' && input[i] != '>' && \
			input[i] != '<' && input[i] != '|' && input[i] != '"' && \
			input[i] != '\'')
	{
		if (input[i] == '$')
		{
			tmp = input;
			input = expander(tmp, &i);
			tmp = free_null(tmp);
		}
		i++;
	}
	word->i = i;
	word->len = i - word->start;
	unquoted = ft_substr(input, word->start, word->len);
	if (!word->str)
		word->str = ft_strdup(unquoted);
	else
	{
		tmp = word->str;
		word->str = ft_strjoin(tmp, unquoted);
		tmp = free_null(tmp);
	}
	free(unquoted);
	if (input[i] && (input[i] == '"' || input[i] == '\''))
		word->str = get_quote(data, input, word, input[i]);
	printf("word->str in get_word: %s\n", word->str);
	return (word->str);
}

int	get_quote_len(char *input, int *i, char quote)
{
	int		len;

	len = 0;
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		len++;
		(*i)++;
	}
	return (len);
}

char	*get_quote(t_data *data, char *input, t_word *word, char quote)
{
	char	*new;
	char	*tmp;
	int		len;
	int		i;

	i = word->i;
	if (input[i] == '$' && quote == '"')
	{
		tmp = input;
		input = expander(tmp, &i);
		free(tmp);
	}
	len = get_quote_len(input, &i, quote);
	if (!len)
		return (NULL);
	new = ft_substr(input, word->i + 1, len);
	if (!new)
		ft_error(MALLOC_ERR, data);
	tmp = word->str;
	word->str = ft_strjoin(tmp, new);
	tmp = free_null(tmp);
	new = free_null(new);
	i++;
	if (input[i] && (input[i] != '"' && input[i] != '\''))
		word->str = get_word(data, input, word);
	// call get_quote again if input[*i] == quotes
	word->i = i;
	printf("word->str in get_quote: %s\n", word->str);
	return (word->str);
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
