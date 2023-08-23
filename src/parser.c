/**
 * @file parser.c
 * @brief Functions initalizing and creating the parser.
 */

#include "parser.h"

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

	tmp = cmd;
	while (*lst && (*lst)->token == WORD)
	{
		*tmp = ft_strdup((*lst)->word);
		if (!*tmp)
			return (1);
		*lst = (*lst)->next;
		tmp++;
	}
	if (!*lst || (*lst)->token == PIPE)
		return (0);
	if ((*lst)->token == INPUT)
		handle_infile(cmd_line, (*lst)->word);
	if ((*lst)->token == OUTPUT || (*lst)->token == APPEND)
		handle_outfile(cmd_line, (*lst)->word, (*lst)->token);
	if ((*lst)->token == HEREDOC)
		handle_heredoc(cmd_line, (*lst)->word);
	if ((*lst)->next)
	{
		*lst = (*lst)->next;
		extract_cmd(data, lst, cmd_line, tmp);
	}
	return (0);
}


// t_lexer *find_end(t_lexer *lst)
// {
// 	while (lst && lst->next)
// 	{
// 		lst = lst->next;
// 	}
// 	return (lst);
// }

// t_lexer *find_start(t_lexer *lst)
// {
// 	while (lst && lst->prev)
// 	{
// 		lst = lst->prev;
// 	}
// 	return (lst);
// }

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
		return (1);
	current_cmd->cmd = arr;
	return (0);
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
int	parser(t_data *data)
{
	t_lexer *lst;
	int		cmd_linelen;
	int		i;

	data->cmds = tkn_counter(data->lex, PIPE, STOP) + 1;
	cmd_linelen = data->cmds + 1;
	data->cmd_line = (t_parse *)ft_calloc(cmd_linelen, sizeof(t_parse));
	if (!data->cmd_line)
		return (1);
	set_ids(data->cmd_line, cmd_linelen);
	lst = data->lex;
	i = 0;
	while (lst)
	{
		if (init_cmd(lst, data->cmd_line + i))
			return (1);
		if (extract_cmd(data, &lst, data->cmd_line + i, data->cmd_line[i].cmd))
			return (1);
		if (i++ == data->cmds - 1)
			break ;
		lst = lst->next;
	}
	return (0);
}
