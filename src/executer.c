
#include "executer.h"

void cmd_printer(t_data *data)
{
	t_parse *tmp;

	tmp = data->cmd_line;
	printf("input: %s\n", data->input);
	printf("cmds: %d\n", data->cmds);
	while (tmp->id != 0)
	{
		printf("cmd[%d]:", tmp->id);
		for (int i = 0; tmp->cmd[i]; i++)
			printf("%s ", tmp->cmd[i]);
		printf("\n");
		printf("infile: %s\n", tmp->infile);
		printf("outfile: %s\n", tmp->outfile);
		printf("append: %d\n", tmp->append);
		printf("heredoc: %s\n", tmp->heredoc);
		tmp++;	
	}
}

void	lexer_printer(t_data *data)
{
	t_lexer *tmp;

	tmp = data->lex;
	while (tmp)
	{
		printf("lex[%d]: %s=%d", tmp->i, tmp->word, tmp->token);
		tmp = tmp->next;
	}
}

char **list_to_arr(t_data *data, t_lstenv *lst)
{
	t_lstenv *tmp;
	int i;
	int j;
	char *str;

	tmp = lst;
	i = 0;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	data->env_arr = ft_calloc(i + 1, sizeof(char *));
	if (!data->env_arr)
		ft_error(MALLOC_ERR, data);
	j = 0;
	while (lst && j <= i)
	{
		str = ft_strjoin(lst->key, "=");
		data->env_arr[j] = ft_strjoin(str, lst->value);
		str = free_null(str);
		j++;
		lst = lst->next;
	}
	return (data->env_arr);
}



int	exec_single_cmd(t_parse *cmd_line, t_data *data)
{
	if (cmd_line->func)
		(*cmd_line->func)(data);
	else
		execve(cmd_line->cmd[0], cmd_line->cmd, list_to_arr(data, data->env));
	return (SUCCESS);
}

int executer(t_data *data)
{
	int	err;

	err = 0;
	cmd_printer(data);
	//create_pipes(data->cmd_line, data);
	if (data->cmds == 1)
		err = exec_single_cmd(data->cmd_line, data);
	// else
	// 	err = exec_multi_cmds(data->cmd_line, data->cmds, data);
	if (err != 0)
		ft_error("ERROR\n", data);
	return (0);	
}