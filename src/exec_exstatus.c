/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exstatus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:15:40 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 16:18:37 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	check_status(int status, int *excode)
{
	int	sig_num;

	if (WIFEXITED(status))
		*excode = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig_num = WTERMSIG(status);
		*excode = 128 + sig_num;
		if (__WCOREDUMP(status))
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (sig_num == SIGINT)
			ft_putchar_fd('\n', 2);
	}
}

void	ft_waitpid(t_data *data, t_parse *cmd)
{
	int	status;

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

int	set_exstat(t_parse *cmd_line, bool *execute, int status)
{
	*execute = false;
	cmd_line->exstatus = status;
	return (status);
}
