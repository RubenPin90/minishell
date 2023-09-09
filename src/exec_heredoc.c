#include "executor.h"

int	heredocfun(t_parse *cmd, char *delim)
{
	int fd;
	char *str;

	fd = open(".tmpfile.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (error_msg("heredoc", strerror(errno)));
	while (1)
	{
		str = readline("");
		if (!str)
		{
			close(fd);
			return (FAIL);
		}
		if (ft_strncmp(str, delim, ft_strlen(delim) + 1) == 0)
			break;
		ft_putendl_fd(str, fd);
		str = free_null(str);
	}
	str = free_null(str);
	if (cmd->fd_in)
		close(cmd->fd_in);
	cmd->fd_in = fd;
	return (SUCCESS);
}

int	find_heredoc(t_parse *cmd, t_lexer *redir)
{
	int ret;

	ret = 0;
	while (redir)
	{
		if (redir->token == HEREDOC)
		{
			//create unique heredoc name and save it in cmd.
			//ft_strdup name to cmd as infile.
			ret = heredocfun(cmd, redir->word);
			if (ret)
				return (ret);
		}
		redir = redir->next;
	}
	return (ret);
}

int	handle_heredoc(t_data *data, t_parse *cmd_line)
{
	int ret;

	ret = 0;
	while (cmd_line->id != 0)
	{
		if (cmd_line->redir)
		{
			ret = find_heredoc(cmd_line, cmd_line->redir);
			if (ret == FAIL)
				ft_error(MALLOC_ERR, data);
			else if (ret == AGAIN)
				return (ret);
		}
		cmd_line++;
	}
	return (ret);
}
