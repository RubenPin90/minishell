/**
 * @file parser.c
 * @brief Functions initalizing and creating the parser.
 */

#include "parser.h"

/**
 * @brief  
 * 
 * @param lst_head 
 * @param eoc 
 * @param cmd 
 * @return int 
 */
void	extract_cmd(t_data *data, t_lexer **lst, int *cmd_id)
{
	(void)*cmd_id;
	while (*lst && (*lst)->token == WORD)
	{
		// 
		*lst = (*lst)->next;
	}
	if (!*lst || (*lst)->token == PIPE)
		return ;
	if ((*lst)->token == INPUT)
	{
		printf("INPUT-FILE: lst[i]: %d, filename: %s\n", (*lst)->i, (*lst)->word);

	}
	if ((*lst)->token == OUTPUT)
		printf("OUTPUT-FILE: lst[i]: %d, filename: %s\n", (*lst)->i, (*lst)->word);
	if ((*lst)->token == APPEND)
		printf("APPEND-FILE: lst[i]: %d, filename: %s\n", (*lst)->i, (*lst)->word);
	if ((*lst)->token == HEREDOC)
		printf("HEREDOC-FILE: lst[i]: %d, filename: %s\n", (*lst)->i, (*lst)->word);
	if ((*lst)->next)
		extract_cmd(data, &(*lst)->next, cmd_id);
	else
		return ;
}

t_lexer *find_end(t_lexer *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_lexer *find_start(t_lexer *lst)
{
	while (lst && lst->prev)
	{
		lst = lst->prev;
	}
	return (lst);
}

void	init_cmd(t_lexer *cmd_list, t_parse *current_cmd)
{
	char **str;
	int	count;

	count = 0;
	while (cmd_list || cmd_list->token != PIPE)
	{
		if (cmd_list->token == WORD)
			count++;
		cmd_list = cmd_list->next;
	}
	str = ft_calloc(count + 1, sizeof(char *));
	if (!str)
		return (1);
	current_cmd->cmd = str;
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
int	parser(t_data *data)
{
	t_lexer *lst;
	int		cmd_id;

	data->cmds = tkn_counter(data->lex, PIPE) + 1;
	data->cmd_line = (t_parse *)ft_calloc(data->cmds, sizeof(t_parse));
	if (!data->cmd_line)
		return (1);
	lst = data->lex;
	cmd_id = 0;
	while (lst)
	{
		init_cmd(lst, data->cmd_line + cmd_id);
		extract_cmd(data, &lst, &cmd_id);
		if (cmd_id++ < data->cmds - 1)
			lst = lst->next;
		else
			break ;
		printf("cmd_line->outfile: %s\n", data->cmd_line->outfile);
	}
	return (0);
}
