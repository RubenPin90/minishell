/**
 * @file parser.c
 * @brief Functions initalizing and creating the parser.
 */

#include "parser.h"

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

int	init_cmd(t_lexer *cmd_list, t_parse *current_cmd)
{
	char **str;
	int	count;

	count = 0;
	while (cmd_list && cmd_list->token != PIPE)
	{
		if (cmd_list->token == WORD)
			count++;
		cmd_list = cmd_list->next;
	}
	str = ft_calloc(count + 1, sizeof(char *));
	if (!str)
		return (1);
	current_cmd->cmd = str;
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
		if (init_cmd(lst, data->cmd_line + cmd_id))
			return (1);
		if (extract_cmd(data, &lst, data->cmd_line + cmd_id, data->cmd_line[cmd_id].cmd))
			return (1);
		printf("cmd_line[%d]->infile: %s\n", cmd_id, data->cmd_line[cmd_id].infile);
		printf("cmd_line[%d]->outfile: %s append: %d\n", cmd_id, data->cmd_line[cmd_id].outfile, data->cmd_line->append);
		printf("cmd_line[%d]->heredoc: %s\n", cmd_id, data->cmd_line[cmd_id].heredoc);
		if (cmd_id++ == data->cmds - 1)
			break ;
		lst = lst->next;
	}
	return (0);
}
