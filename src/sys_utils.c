#include "minishell.h"

void cmd_printer(t_data *data)
{
	t_parse *tmp;

	tmp = data->cmd_line;
	printf(YELLOW"_______CMD_PRINTER_______\n\n"RESET);
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
		lexer_printer(tmp->redir, false);
		printf("fd_in: %d, fd_out: %d\n", tmp->fd_in, tmp->fd_out);
		tmp++;	
	}
}

void	lexer_printer(t_lexer *lex, int check)
{
	t_lexer *tmp;

	tmp = lex;
	if (check)
		printf(YELLOW"_______LEX_PRINTER_______\n\n"RESET);
	while (tmp)
	{
		printf("lex[%d]: %s=%d\n", tmp->i, tmp->word, tmp->token);
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

char **arr_expand(char **arr, char *str)
{
	int		i;
	int		arrlen;
	char	**new_arr;

	if (!arr && !str)
		return (NULL);
	arrlen = 0;
	if (arr)
		arrlen = ft_arrlen(arr);
	new_arr =  ft_calloc(arrlen + 1, sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = -1;
	while(++i < arrlen)
		new_arr[i] = arr[i];
	new_arr[i] = ft_strdup(str);
	if (!new_arr[i])
		new_arr = free_arr(new_arr);
	arr = free_arr(arr);
	return (new_arr);
}

int	ft_arrlen(char **arr)
{
	int i;

	i = 0;
	while(arr && arr[i])	
		i++;
	return(i);
}