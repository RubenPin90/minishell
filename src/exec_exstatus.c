
#include "executor.h"

void check_status(int status, int *excode)
{
	int sig_num;

	if (WIFEXITED(status))
	{
		printf("before: %d\n", *excode);
		*excode = WEXITSTATUS(status);
		printf("after: %d\n", *excode);
	}
	else if (WIFSIGNALED(status))
	{
		sig_num = WTERMSIG(status);
		printf("sig_num: %d\n", sig_num);
		*excode = 128 + sig_num;
		if (__WCOREDUMP(status))
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (sig_num == SIGINT)
			ft_putchar_fd('\n', 2);
	}
}

void ft_waitpid(t_data *data, t_parse *cmd)
{
	int status;

	while (cmd->id != 0)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			check_status(status, &data->excode);
		}
		cmd++;
	}
}
