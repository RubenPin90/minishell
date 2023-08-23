
#include "minishell.h"

void	check_buildin(t_data *data)
{
	char	*buf;

	buf = NULL;
	if (!ft_strncmp(data->input, "pwd", 3))
	{
		buf = ft_pwd(data);
		ft_printf("%s\n", buf);
		buf = free_null(buf);
	}
	if (!ft_strncmp(data->input, "env", 3))
		print_env(data->env);
	if (!ft_strncmp(data->input, "exit", 4))
		ft_exit(data);
}

/*
*/
char	*ft_pwd(t_data *data)
{
	char	*buf;
	int		size;

	(void)data;
	size = 2;
	buf = ft_calloc(sizeof(char), size);
	if (!buf)
		return (NULL);
	while (size < 10000)
	{
		if (getcwd(buf, size) != NULL)
			return (buf);
		else
		{
			free(buf);
			size += 1;
			buf = ft_calloc(sizeof(char), size);
		}
	}
	buf = free_null(buf);
	return (NULL);
}

void	ft_exit(t_data *data)
{
	ft_printf("exit\n");
	ft_cleanup(data);
	exit(0);
}


// int main()
// {
// 	char *buf;

// 	buf = NULL;
// 	buf = ft_pwd(buf);
// 	printf("%s\n", buf);
// 	free(buf);
// }

