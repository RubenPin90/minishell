#include "executor.h"

int	heredocfun(t_data *data, t_parse *cmd, char *delim)
{
	int		fd;
	char	*str;

	fd = open(cmd->heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (error_msg("heredoc", NULL, strerror(errno)));
	while (g_signum != SIGINT)
	{
		str = readline("");
		if (!str)
		{
			cleanup_fd(&fd);
			return (FAIL);
		}
		data->quoted = true;
		str = expander(data, str);
		if (ft_strncmp(str, delim, ft_strlen(delim) + 1) == 0)
			break ;
		if (g_signum != SIGINT)
			ft_putendl_fd(str, fd);
		str = free_null(str);
	}
	str = free_null(str);
	cleanup_fd(&fd);
	return (SUCCESS);
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
	while (redir)
	{
		if (redir->token == HEREDOC)
		{
			handle_signals(true);
			if (heredocfun(data, cmd, redir->word))
				return (error_msg("warning", HERE_STOP_ERR, redir->word));
			handle_signals(false);
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
