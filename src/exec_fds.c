#include "executor.h"

int	handle_fds(t_data *data, t_parse *cmd)
{
	while (cmd->id != 0)
	{
		if(cmd->redir)
		{
			handle_infile(data, cmd, cmd->redir);
			handle_outfile(data, cmd, cmd->redir);
		}
		cmd++;
	}
	return (SUCCESS);
}


int	handle_infile(t_data *data, t_parse *cmd, t_lexer *redir)
{
	int fd;
	bool update_fd;

	fd = -1;
	update_fd = false;
	(void)data;
	while (redir)
	{
		if (redir->token == HEREDOC)
			update_fd = false;
		if (redir->token == INPUT)
		{
			if (fd != -1)
				close(fd);
			fd = open(redir->word, O_RDONLY);
			if (fd == -1)
				return (error_msg(redir->word, strerror(errno)));
			update_fd = true;
		}
		redir = redir->next;
	}
	if (update_fd && cmd->fd_in)
	{
		close(cmd->fd_in);
		//unlink old file and free str.
		cmd->fd_in = fd;
	}
	else if (update_fd && !cmd->fd_in )
		cmd->fd_in = fd;
	else
		close(fd);
	return (SUCCESS);
}

int	handle_outfile(t_data *data, t_parse *cmd, t_lexer *redir)
{
	int fd;

	fd = -1;
	(void)data;
	while (redir)
	{
		if (redir->token == APPEND)
		{
			if (fd != -1)
				close(fd);
			fd = open(redir->word, O_RDWR | O_APPEND | O_CREAT, 0644);
			if (fd == -1)
				return (error_msg(redir->word, FD_ACCESS_ERR));
		}
		if (redir->token == OUTPUT)
		{
			if (fd != -1)
				close(fd);
			fd = open(redir->word, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (error_msg(redir->word, FD_ACCESS_ERR));
		}
		redir = redir->next;
	}
	cmd->fd_out = fd;
	return (SUCCESS);
}
