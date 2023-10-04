#include "executor.h"

int	heredocfun(t_data *data, t_parse *cmd, char *delim)
{
	int		fd;
	char	*str;

	fd = open(cmd->heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (error_msg("heredoc", NULL, strerror(errno), AGAIN));
	while (1)
	{
		str = readline("");
		if (!str)
			return (cleanup_herefun(&str, &fd, FAIL));
		if (g_signum == SIGINT)
			return (cleanup_herefun(&str, &fd, AGAIN));
		data->quoted = true;
		str = expander(data, str);
		if (!ft_strncmp(str, delim, ft_strlen(delim) + 1))
			break ;
		ft_putendl_fd(str, fd);
		str = free_null(str);
	}
	return (cleanup_herefun(&str, &fd, SUCCESS));
}

int	cleanup_herefun(char **str, int *fd, int ret)
{
	cleanup_fd(fd);
	if (ret != FAIL)
		*str = free_null(*str);
	return (ret);
}

void	heredoc_name(t_data *data, t_parse *cmd)
{
	char *id;

	id = ft_itoa(cmd->id);
	if (!id)
		ft_error(MALLOC_ERR, data);
	cmd->heredoc = ft_strjoin(".herefile_cmd", id);
	id = free_null(id);
	if (!cmd->heredoc)
		ft_error(MALLOC_ERR, data);
}

int	find_heredoc(t_data *data, t_parse *cmd, t_lexer *redir)
{
	int	ret;

	ret = SUCCESS;
	while (redir)
	{
		if (redir->token == HEREDOC)
		{
			handle_signals(true);
			ret = heredocfun(data, cmd, redir->word);
			handle_signals(false);
			if (ret == FAIL)
				return (error_msg("warning", HERE_STOP_ERR, redir->word, AGAIN));
			else if (ret == AGAIN)
				return (AGAIN);
		}
		redir = redir->next;
	}
	return (SUCCESS);
}

int	handle_heredoc(t_data *data, t_parse *cmd_line)
{
	while (cmd_line->id != 0)
	{
		if (cmd_line->redir && tkn_counter(cmd_line->redir, HEREDOC, STOP))
		{
			heredoc_name(data, cmd_line);
			if (find_heredoc(data, cmd_line, cmd_line->redir))
				return (AGAIN);
		}
		cmd_line++;
	}
	return (SUCCESS);
}
