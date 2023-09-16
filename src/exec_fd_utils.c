#include "executor.h"

int	cleanup_fd(int *fd, char **filename)
{
	if (*fd >= 0)
	{
		if (close(*fd) < 0)
			return (FAIL);
			//error_msg(*filename, strerror(errno));
		*fd = -1; 
	}
	if (*filename)
		*filename = free_null(*filename);
	return (SUCCESS);
}

int update_fd(bool check, t_parse *cmd, char **name, int fd)
{
	if (check == true)
	{
		if (cmd->infile)
		{
			unlink(cmd->infile);
			cleanup_fd(&cmd->fd_in, &cmd->infile);
		}
		cmd->fd_in = fd;
		cmd->infile = *name;
	}
	else
		cleanup_fd(&fd, name);
	return (SUCCESS);
}

int	ft_open(char *file, t_type token)
{
	int fd;

	if (token == APPEND)
		fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	else if (token == OUTPUT)
		fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	else if (token == INPUT)
		fd = open(file, O_RDONLY);
	if (fd == -1)
		error_msg(file, strerror(errno));
	return (fd);
}
