#include "builtin.h"

char *get_pwd(void)
{
	char	*buf;
	int		size;
	char	*ret;

	size = 4000;
	while (size < 8001)
	{
		buf = ft_calloc(sizeof(char), size);
		if (!buf)
			return (NULL);
		ret = getcwd(buf, size);
		if (!ret)
		{
			size *= 2;
			buf = free_null(buf);
		}
		else 
			break ;
	}
	return (ret);
}

int	ft_pwd(t_data *data, t_parse *cmd)
{
	char *buf;

	(void)data;
	(void)cmd;
	buf = get_pwd();
	if (!buf)
	{
		error_msg("pwd", NULL, strerror(errno));
		return (FAIL);
	}
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	buf = free_null(buf);
	return (SUCCESS);
}
