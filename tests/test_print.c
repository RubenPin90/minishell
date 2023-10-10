
#include "minishell.h"

void	cmd_printer(t_data *data)
{
	t_parse *tmp;
	t_lexer *tmp2;
	// struct stat file_stat;

	tmp = data->cmd_line;
	tmp2 = data->exp_lst;
	printf(YELLOW"PID%d_______CMD_PRINTER_______\n\n"RESET, tmp->pid);
	printf(YELLOW"input:"RESET" %s\n", data->input);
	printf(YELLOW"cmds:"RESET" %d\n", data->cmds);
	while (tmp2)
	{
		printf(YELLOW"exp_lst:"RESET" %s\n", tmp2->word);
		tmp2 = tmp2->next;
	}
	while (tmp->id != 0)
	{
		if (tmp->id > 1)
			printf(RED"|---------------------------|\n"RESET);
		printf(YELLOW"execute:"RESET" %d\n", tmp->execute);
		printf(YELLOW"cmd_path:"RESET" %s\n", tmp->cmd_path);
		printf(YELLOW"cmd[%d]:"RESET, tmp->id);
		if (tmp->cmd)
		{
			for (int i = 0; tmp->cmd[i]; i++)
				printf("%s ", tmp->cmd[i]);
			printf("\n");
		}
		lexer_printer(tmp->redir, false);
		printf(YELLOW"infile:"RESET" %s\n", tmp->infile);
		printf(YELLOW"heredoc:"RESET" %s\n", tmp->heredoc);
		printf(YELLOW"outfile:"RESET" %s\n", tmp->outfile);
		printf(YELLOW"fd_in:"RESET" %d "YELLOW"fd_out:"RESET" %d\n", tmp->fd_in, tmp->fd_out);
		printf(YELLOW"fd_pipes[0]:"RESET" %d "YELLOW"fd_pipes[1]:"RESET" %d\n", tmp->fd_pipes[0], tmp->fd_pipes[1]);
    	if (isatty(fileno(stdin)) == 0) {
        	printf(BLUE"stdin is a file"RESET" [%d]%s\n", STDIN_FILENO, ttyname(STDIN_FILENO));
		}
    	if (isatty(fileno(stdout)) == 0) {
        	printf(BLUE"stdout is a file"RESET" [%d]%s\n", STDOUT_FILENO, ttyname(STDOUT_FILENO));
		}
		tmp++;
	}
}

void	lexer_printer(t_lexer *lex, int check)
{
	t_lexer	*tmp;

	tmp = lex;
	if (check)
	{
		printf(YELLOW"_______LEX_PRINTER_______\n\n"RESET);
		while (tmp)
		{
			printf("lex[%d]: %s=%d\n", tmp->i, tmp->word, tmp->token);
			tmp = tmp->next;
		}
	}
	else
	{
		printf(YELLOW"redir: "RESET);
		while (tmp)
		{
			printf("[%d]%s ", tmp->token, tmp->word);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

// #include "expander.h"

// NOTE: delete this function
// void	print_lexlst(t_data *data)
// {
// 	t_lexer	*tmp = data->lex;

// 	tmp = data->lex;
// 	while (tmp)
// 	{
// 		printf("lex[%d]: %s\n", tmp->i, tmp->word);
// 		tmp = tmp->next;
// 	}
// }