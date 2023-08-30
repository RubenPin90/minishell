
#include "minishell.h"
#include <errno.h>

int	check_buildin(t_parse *cmd_line, char *cmd)
{
	int len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "pwd", len))
		cmd_line->func = &ft_pwd;
	else if (!ft_strncmp(cmd, "env", len))
		cmd_line->func = &print_env;
	else if (!ft_strncmp(cmd, "exit", len))
		cmd_line->func = &ft_exit;
	else if (!ft_strncmp(cmd, "export", len))
		printf("export\n");
		// cmd_line->func = &ft_export;
	else if (!ft_strncmp(cmd, "cd", len))
		printf("cd\n");
		// cmd_line->func = &ft_cd;
	else if (!ft_strncmp(cmd, "echo", len))
		printf("echo\n");
		// cmd_line->func = &ft_echo;
	else if (!ft_strncmp(cmd, "unset", len))
		printf("unset\n");
		// cmd_line->func = &ft_unset;
	else
		return (FAIL);
	return (SUCCESS);
}

/*
*/
int	ft_pwd(t_data *data)
{
	char	buf[8000];
	int		size;

	(void)data;
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

int	ft_exit(t_data *data)
{
	ft_printf("exit\n");
	ft_cleanup(data, true);
	exit(0);
	return (SUCCESS);
}


// int main()
// {
// 	char *buf;

// 	buf = NULL;
// 	buf = ft_pwd(buf);
// 	printf("%s\n", buf);
// 	free(buf);
// }

