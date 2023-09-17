#include "builtin.h"

int	ft_pwd(t_data *data, t_parse *cmd)
{
	char	buf[8000];
	int		size;

	(void)data;
	(void)cmd;
	size = 4000;
	while (size < 8001)
	{
		if (!getcwd(buf, size) && errno == ERANGE)
			size *= 2;
		else 
			break ;
	}
	if (getcwd(buf, size) == NULL)
		return(error_msg("pwd", strerror(errno)));
	else
		ft_printf("%s\n", buf);
	return (SUCCESS);
}