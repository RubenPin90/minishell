#include "parser.h"

bool	ft_push_redir(t_lexer **a, t_lexer **b, bool first)
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
		first = true;
	}
	else
		*a = NULL;
	lexer_addback(b, tmp);
	return (first);
}

int	extract_cmd(t_data *data, t_lexer **lst, t_parse *cmd_line, char **cmd)
{
	char	**tmp;
	bool	first;

	tmp = cmd;
	first = false;
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
	first = ft_push_redir(lst, &cmd_line->redir, first);
	if (!*lst || (first == false && !(*lst)->next))
		return (SUCCESS);
	if (first == false)
		*lst = (*lst)->next;
	extract_cmd(data, lst, cmd_line, tmp);
	return (SUCCESS);
}

int	init_cmd(t_lexer *cmd_list, t_parse *current_cmd)
{
	char	**arr;
	int		count;

	count = 0;
	count = tkn_counter(cmd_list, WORD, PIPE);
	arr = ft_calloc(count + 1, sizeof(char *));
	if (!arr)
		return (FAIL);
	current_cmd->cmd = arr;
	current_cmd->fd_in = -1;
	current_cmd->fd_out = -1;
	current_cmd->fd_pipes[0] = -1;
	current_cmd->fd_pipes[1] = -1;
	current_cmd->execute = true;
	current_cmd->exstatus = E_SUCCESS;
	return (SUCCESS);
}

void	set_ids(t_parse *cmd_line, int len)
{
	int	i;

	i = 1;
	while (i < len)
	{
		cmd_line->id = i;
		cmd_line++;
		i++;
	}
	cmd_line->id = 0;
}

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
	while (lst && lst->prev)
		lst = lst->prev;
	data->lex = lst;
	return (SUCCESS);
}
