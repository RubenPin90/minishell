#include "executor.h"

void	handle_fds(t_parse *cmd)
{
	while (cmd->id != 0)
	{
		if (cmd->redir && (tkn_counter(cmd->redir, INPUT, STOP) || \
							tkn_counter(cmd->redir, HEREDOC, STOP)))
			handle_infile(cmd, cmd->redir);
		if (cmd->redir && (tkn_counter(cmd->redir, OUTPUT, STOP) || \
							tkn_counter(cmd->redir, APPEND, STOP)))
			handle_outfile(cmd, cmd->redir);
		cmd++;
	}
}

void	handle_infile(t_parse *cmd, t_lexer *redir)
{
	while (redir)
	{
		if (redir->token == INPUT || redir->token == HEREDOC)
		{
			cleanup_fd(&cmd->fd_in);
			cmd->infile = free_null(cmd->infile);
			cmd->fd_in = ft_open(redir->word, redir->token, cmd->heredoc);
			if (cmd->fd_in == -1)
			{
				switch_cmd_status(cmd, &cmd->execute, E_ERROR);
				return ;
			}
			if (redir->token == INPUT)
			{
				cmd->infile = ft_strdup(redir->word);
				if (!cmd->infile)
					cleanup_fd(&cmd->fd_in); 
			}
		}
		redir = redir->next;
	}
	update_fd(cmd, &cmd->infile);
}

void	handle_outfile(t_parse *cmd, t_lexer *redir)
{
	while (redir)
	{
		if (redir->token == APPEND || redir->token == OUTPUT)
		{
			cleanup_fd(&cmd->fd_out);
			cmd->outfile = free_null(cmd->outfile);
			cmd->fd_out = ft_open(redir->word, redir->token, NULL);
			if (cmd->fd_out == -1)
			{
				switch_cmd_status(cmd, &cmd->execute, E_ERROR);
				return ;
			}
			cmd->outfile = ft_strdup(redir->word);
			if (!cmd->outfile)
				cleanup_fd(&cmd->fd_out);
		}
		redir = redir->next;
	}
}
