#include "executor.h"

int	heredocfun(t_data *data, t_parse *cmd, char *delim)
{
	int fd;
	char *str;

	fd = open(cmd->heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (error_msg("heredoc", strerror(errno)));
	while (1)
	{
		str = readline("");
		if (!str)
		{
			cleanup_fd(&fd);
			return (FAIL);
		}
		data->quoted = true;
		str = expander(data, str);
		printf("str: %s\n", str);
		if (ft_strncmp(str, delim, ft_strlen(delim) + 1) == 0)
			break;
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
	int ret;

	ret = 0;
	while (redir)
	{
		if (redir->token == HEREDOC)
		{
			ret = heredocfun(data, cmd, redir->word);
			if (ret == FAIL)
				ft_error(MALLOC_ERR, data);
		}
		redir = redir->next;
	}
	return (ret);
}

void	handle_heredoc(t_data *data, t_parse *cmd_line)
{
	while (cmd_line->id != 0)
	{
		if (cmd_line->redir && tkn_counter(cmd_line->redir, HEREDOC, STOP))
		{
			heredoc_name(data, cmd_line);
			find_heredoc(data, cmd_line, cmd_line->redir);
		}
		cmd_line++;
	}
}
