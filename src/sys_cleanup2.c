/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_cleanup2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:56:09 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 13:58:37 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse	*free_parser(t_parse *cmdl)
{
	t_parse	*start;

	start = cmdl;
	while (cmdl->id != 0)
	{
		if (cmdl->cmd)
			cmdl->cmd = free_arr(cmdl->cmd);
		if (cmdl->cmd_path)
			cmdl->cmd_path = free_null(cmdl->cmd_path);
		if (cmdl->infile)
			cmdl->infile = free_null(cmdl->infile);
		if (cmdl->outfile)
			cmdl->outfile = free_null(cmdl->outfile);
		if (cmdl->heredoc)
		{
			unlink(cmdl->heredoc);
			cmdl->heredoc = free_null(cmdl->heredoc);
		}
		if (cmdl->redir)
			free_lexer(&cmdl->redir);
		cmdl++;
	}
	start = free_null(start);
	return (start);
}

void	free_lexer(t_lexer **lex)
{
	t_lexer	*tmp;

	tmp = *lex;
	while (*lex)
	{
		tmp = (*lex)->next;
		if ((*lex)->word)
			free((*lex)->word);
		free(*lex);
		*lex = tmp;
	}
	*lex = NULL;
}
