
#include "minishell.h"

void	check_buildin(t_data *data)
{
	char	*buf;

	buf = NULL;
	if (!ft_strncmp(data->input, "pwd", 3))
	{
		buf = ft_pwd(data);
		ft_printf("%s\n", buf);
		free(buf);
	}
	if (!ft_strncmp(data->input, "env", 3))
		print_env(data->env);
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
		exit (1); //add exit function
	while(1)
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
}

// int main()
// {
// 	char *buf;

// 	buf = NULL;
// 	buf = ft_pwd(buf);
// 	printf("%s\n", buf);
// 	free(buf);
// }

