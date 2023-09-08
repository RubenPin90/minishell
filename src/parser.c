/**
 * @file parser.c
 * @brief Functions initalizing and creating the parser.
 */

#include "parser.h"

int	handle_redir(t_data *data, t_type token, t_parse *cmd_line, char *word)
{
	int ret;

	ret = SUCCESS;
	if (token == INPUT || token == HEREDOC)
		ret = handle_infile(cmd_line, word, token);
	if (token == OUTPUT || token == APPEND)
		ret = handle_outfile(cmd_line, word, token);
	// if (token == HEREDOC)
	// 	ret = handle_heredoc(cmd_line, word);
	if (ret == FAIL)
		ft_error(MALLOC_ERR, data);
	return (ret);
}

int	add_redir(t_parse *cmd_line, t_lexer *node)
{
	if (!cmd_line->redir)
		cmd_line->redir = node;
	return(SUCCESS);
}


bool	ft_push_redir(t_lexer **a, t_lexer **b, bool check)
{
	t_lexer	*tmp;

	tmp = *a;
	if ((*a)->prev && (*a)->next)
	{
		(*a)->prev->next = (*a)->next;
		(*a)->next->prev = (*a)->prev;
		*a = (*a)->prev;
	}
	else if ((*a)->prev && !(*a)->next)
	{
		(*a)->prev->next = NULL;
		*a = (*a)->prev;
	}
	else if (!(*a)->prev && (*a)->next)
	{
		(*a)->next->prev = NULL;
		*a = (*a)->next;
		check = true;
	}
	else
		*a = NULL;
	lexer_addback(b, tmp);
	return (check);
}

/**
 * @brief Transfer and assign tokens into each command.  
 * 
 * Loops through list, changing the list pointer address, and as long as type of node is WORD
 * copies the word of the node into the 2D array in t_parse. Checks if PIPE or end of list is
 * reached. If not, handles node accordingly to its type. If list->next exists calls function
 * recursivly.
 * @param data General data struct.
 * @param lst Modified tokinezed lexer list (not always at the start).
 * @param cmd_line Array of commands at current position (cmd_id).
 * @param cmd 2D array of t_parse at current position (cmd_id).
 * @return int 
 */
int	extract_cmd(t_data *data, t_lexer **lst, t_parse *cmd_line, char **cmd)
{
	char **tmp;
	bool check;

	tmp = cmd;
	check = false;
	while (*lst && (*lst)->token == WORD)
	{
		*tmp = ft_strdup((*lst)->word);
		if (!*tmp)
			ft_error(MALLOC_ERR, data);
		if (!(*lst)->next)
			return (SUCCESS);
		*lst = (*lst)->next;
		tmp++;
	}
	if ((*lst)->token == PIPE)
		return (SUCCESS);
	check = ft_push_redir(lst, &cmd_line->redir, check);
	if (!*lst || (check == false && !(*lst)->next))
		return (SUCCESS);
	if (check == false)
		*lst = (*lst)->next;
	extract_cmd(data, lst, cmd_line, tmp);
	return (SUCCESS);
}

/**
 * @brief Initializing t_parse struct for current cmd
 * 
 * Loops through lexer list, counts all the words until it 
 * list->next is a pipe or NULL --> amount of words in current cmd.
 * Calloc that amount and store it in t_parse.
 * @param cmd_list Tokenized input list, starting from beginning or after pipe.
 * @param current_cmd Cmd struct array at position cmd_id.
 * @return int 1 for error. 0 for SUCCESS.
 */
int	init_cmd(t_lexer *cmd_list, t_parse *current_cmd)
{
	char **arr;
	int	count;

	count = 0;
	count = tkn_counter(cmd_list, WORD, PIPE);
	arr = ft_calloc(count + 1, sizeof(char *));
	if (!arr)
		return (FAIL);
	current_cmd->cmd = arr;
	return (SUCCESS);
}

void set_ids(t_parse *cmd_line, int len)
{
	int i;

	i = 1;
	while (i < len)
	{
		cmd_line->id = i;
		cmd_line++;
		i++;
	}
	cmd_line->id = 0;
}
/**
 * @brief Convertes lexer list to each command. 
 * 
 * Counts number of commands by counting pipes + 1 (at least 1 command).
 * Callocs an array of t_parse size of number of commands.
 * Loops through the lexer list initates all strings and arrays in t_parse
 * on position cmd_id. Exctracts cmd into t_parse and increases cmd_id. If cmd_id reaches
 * amount of cmds, it means all commands are extracted --> break.
 * @param data General data struct.
 * @return int 1 if error; 0 if success
*/
int	parser(t_data *data, t_lexer *lst)
{
	int		cmd_linelen;
	int		i;

	data->cmds = tkn_counter(data->lex, PIPE, STOP) + 1;
	cmd_linelen = data->cmds + 1;
	data->cmd_line = (t_parse *)ft_calloc(cmd_linelen, sizeof(t_parse));
	if (!data->cmd_line)
		ft_error(MALLOC_ERR, data);
	set_ids(data->cmd_line, cmd_linelen);
	i = 0;
	while (lst)
	{
		if (init_cmd(lst, data->cmd_line + i))
			ft_error(MALLOC_ERR, data);
		extract_cmd(data, &lst, data->cmd_line + i, data->cmd_line[i].cmd);
		if (i++ == data->cmds - 1)
			break ;
		lst = lst->next;
	}
	while(lst && lst->prev)
		lst = lst->prev;
	return (SUCCESS);
}
