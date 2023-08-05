/*#file: test_parser.c
**#descr: Containing functions for creating the parser.
*/
#include "minishell.h"

/**
 * @brief Grouping lexer input list together into cmds.
 * 
 */
typedef struct s_parse
{
	char			*cmd_link;
	char			**cmd;
	char			*infile;
	char			*outfile;
	char			*heredoc;
	int				num_redir;
}	t_parse;

/**
 * @brief Counting token in lexer.
 *
 * Loops through linked list, increases count with
 * each token, starting from 0. 
 * @param lex Tokenized input list.
 * @param tkn Token to be searched.
 * @return int Number of token.
 */
int tkn_counter(t_lexer *lex, t_token tkn)
{
	int count;

	count = 0;
	while (lex)
	{
		if (lex->token == tkn)
			count++;
		lex = lex->next;
	}
	return (count);
}

int	handle_redir(t_lexer **lex, int eoc, t_parse *cmd)
{
	t_lexer *lst;
	t_lexer *tmp;
	int		num_redir;

	lst = *lex;
	num_redir = tkn_counter(lex, OUTPUT) + 1;
	while (lst->i <= eoc)
	{
		if (lst->token >= INPUT || lst->token <= APPEND)
		{
			

		}
		lst = lst->next;
	}
}

int	handle_heredoc(t_lexer **lst, int eoc, t_parse *cmd)
{}

int	handle_cmd(t_lexer **lst, int eoc, t_parse *cmd)
{}


/**
 * @brief  
 * 
 * @param lst_head 
 * @param eoc 
 * @param cmd 
 * @return int 
 */
int	extract_cmd(t_lexer **lst_head, int eoc, t_parse *cmd)
{
	if (handle_redir(lst_head, eoc, cmd))
		return (1);
	if (handle_heredoc(lst_head, eoc, cmd))
		return (1);
	if (handle_cmd(lst_head, eoc, cmd))
		return (1);
	return (0);
}
/**
 * @brief Convertes lexer list to each command. 
 * 
 * Callocs an array of t_parse size of number of commands.
 * Loops through the lexer linked list until it finds a '|' or NULL
 * in the next node. Calls extract_cmd to do the necessary steps to
 * extract the important infos of that cmd.
 * @param data General data struct.
 * @param lex Tokenized input list.
 * @param cmd_line Struct array of cmds.
 * @return int 1 if error; 0 if success
*/
int	parser(t_data *data, t_lexer *lex, t_parse **cmd_line)
{
	t_lexer	*start;
	int		cmd_size;
	int		cmd_id;

	data->cmds = tkn_counter(lex, PIPE) + 1;
	*cmd_line = ft_calloc(sizeof(t_parse *), data->cmds);
	if (!*cmd_line)
		return (1);
	start = lex;
	cmd_id = 0;
	while (lex)
	{
		if (lex->next->token == PIPE && lex->next == NULL)
		{
			if(extract_cmd(&start, lex->i, cmd_line[cmd_id++]))
				return (1);
			lex = lex->next;
		}
		if (lex)
			lex = lex->next;
	}
	return (0);
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
		free(*lex);
		*lex = tmp;
	}
	*lex = NULL;
}

int	test_parser(void)
{
	t_lexer	*lex;
	t_lexer	*start;
	t_parse	*cmd_line;
	t_data	data;

	lex = NULL;
	lexer_addback(&lex, new_lexer_node("ls", 0));
	lexer_addback(&lex, new_lexer_node("-la", 0));
	lexer_addback(&lex, new_lexer_node(0, 1));
	lexer_addback(&lex, new_lexer_node("wc", 0));
	lexer_addback(&lex, new_lexer_node("-l", 0));

	start = lex;
	while (lex)
	{
		printf("%s ", lex->word);
		lex = lex->next;
	}
	lex = start;
	if (parser(&data, lex, &cmd_line))
	{
		free_lexer(&lex);
		return (1);
	}
	free_lexer(&lex);
	free(cmd_line);
	return (0);
}


