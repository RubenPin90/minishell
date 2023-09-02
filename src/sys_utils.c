#include "minishell.h"

void cmd_printer(t_data *data)
{
	t_parse *tmp;

	tmp = data->cmd_line;
	printf("input: %s\n", data->input);
	printf("cmds: %d\n", data->cmds);
	while (tmp->id != 0)
	{
		printf("cmd_path: %s\n", tmp->cmd_path);
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

int	lex_len(t_lstenv *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char *ft_strjoin_wrapper(char *str1, char*str2, char *str3)
{
	char *tmp;
	char *strnew;

	strnew = ft_strjoin(str1, str2);
	if (!strnew)
		return (NULL);
	tmp = strnew;
	strnew = ft_strjoin(strnew, str3);
	if (!strnew)
	{
		tmp = free_null(tmp);
		return (NULL);
	}
	tmp = free_null(tmp);
	return(strnew);
}
