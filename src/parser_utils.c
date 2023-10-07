#include "parser.h"

int	tkn_counter(t_lexer *lex, t_type tkn, t_type end)
{
	int	count;

	count = 0;
	while (lex && lex->token != end)
	{
		if (lex->token == tkn)
			count++;
		lex = lex->next;
	}
	return (count);
}

t_parse	*free_parser(t_parse *cmd_line)
{
	t_parse	*start;

	start = cmd_line;
	while (cmd_line->id != 0)
	{
		if (cmd_line->cmd)
			cmd_line->cmd = free_arr(cmd_line->cmd);
		if (cmd_line->cmd_path)
			cmd_line->cmd_path = free_null(cmd_line->cmd_path);
		if (cmd_line->infile)
			cmd_line->infile = free_null(cmd_line->infile);
		if (cmd_line->outfile)
			cmd_line->outfile = free_null(cmd_line->outfile);
		if (cmd_line->heredoc)
		{
			unlink(cmd_line->heredoc);
			cmd_line->heredoc = free_null(cmd_line->heredoc);
		}
		if (cmd_line->redir)
			free_lexer(&cmd_line->redir);
		cmd_line++;
	}
	start = free_null(start);
	return (start);
}
