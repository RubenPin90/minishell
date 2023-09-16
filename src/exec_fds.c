#include "executor.h"

int	handle_fds(t_data *data, t_parse *cmd)
{
	while (cmd->id != 0)
	{
		if(cmd->redir && tkn_counter(cmd->redir, INPUT, STOP))
			if (handle_infile(data, cmd, cmd->redir))
				return (AGAIN);
		if (cmd->redir && (tkn_counter(cmd->redir, OUTPUT, STOP) || \
							tkn_counter(cmd->redir, APPEND, STOP)))
			if (handle_outfile(data, cmd, cmd->redir))
				return (AGAIN);
		cmd++;
	}
	return (SUCCESS);
}

int	handle_infile(t_data *data, t_parse *cmd, t_lexer *redir)
{
	int fd;
	char *tmp;
	bool update;

	fd = -1;
	tmp = NULL;
	update = false;
	(void)data;
	while (redir)
	{
		if (redir->token == HEREDOC)
			update = false;
		else if (redir->token == INPUT)
		{
			update = true;
			cleanup_fd(&fd);
			tmp = free_null(tmp);
			fd = ft_open(redir->word, redir->token);
			if (fd == -1)
				return (AGAIN);
			tmp = ft_strdup(redir->word);
			if (!tmp)
				cleanup_fd(&fd); // doesnt have to be protected. If NULL it solves itself
		}
		redir = redir->next;
	}
	update_fd(update, cmd, &tmp, fd);
	return (SUCCESS);
}

int	handle_outfile(t_data *data, t_parse *cmd, t_lexer *redir)
{
	int fd;
	char *tmp;

	fd = -1;
	tmp = NULL;
	while (redir)
	{
		cleanup_fd(&fd);
		tmp = free_null(tmp);
		if (redir->token == APPEND || redir->token == OUTPUT)
		{
			fd = ft_open(redir->word, redir->token);
			if (fd == -1)
				return (AGAIN);
			tmp = ft_strdup(redir->word);
			if (!tmp)
			{
				cleanup_fd(&fd);
				ft_error(MALLOC_ERR, data);
			}
		}
		redir = redir->next;
	}
	cmd->fd_out = fd;
	cmd->outfile = tmp;
	return (SUCCESS);
}
