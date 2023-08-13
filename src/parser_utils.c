/**
 * @file parser_utils.c
 * @brief Helper functions to create the parser. 
 */

#include "parser.h"



/**
 * @brief Counting token in lexer.
 *
 * Loops through linked list, increases count with
 * each token, starting from 0. 
 * @param lex Tokenized input list.
 * @param tkn Token to be searched.
 * @return int Number of token.
 */
int tkn_counter(t_lexer *lex, t_token tkn)
{
	int count;

	count = 0;
	while (lex)
	{
		if (lex->token == tkn)
			count++;
		lex = lex->next;
	}
	return (count);
}

void	del_node(t_lexer **n_prev, t_lexer **node, t_lexer **n_next)
{
	t_lexer *tmp;

	tmp = *node;
	if (*n_prev && *n_next)
	{
		(*n_prev)->next = *n_next;
		(*n_next)->prev = *n_prev;
		*node = *n_next;
	}
	else if (*n_prev && !*n_next)
	{
		(*n_prev)->next = NULL;
		*node = NULL;
	}
	else if (!*n_prev)
	{
		*node = *n_next;
		(*node)->prev = NULL;
	}
	free(tmp->word);
	free(tmp);
}



			
/**
 * @brief If cmd has redir-token, add it into cmd_line.   
 * 
 * Loop through cmd and if redir-token will be found, the node and
 * the next node, will be cut out of the lexer list and added to the
 * cmd_line t_parse struct array.
 * @param lex Tokenized input list.
 * @param eoc End of Command (index of node where cmd ends).
 * @param cmd Command struct, where the cmd infos are saved. 
 * @return int 
 */
int	handle_redir(t_lexer **lex, int eoc, t_parse *cmd)
{
	t_lexer *lst;
	// t_lexer *tmp;

	lst = *lex;
	// printf("eoc: %d\n", eoc);
	while (lst && lst->i <= eoc)
	{
		printf("REDIR: lst->i: %d lst->token: %d outfile: %s\n", lst->i, lst->token, cmd->outfile);
		if (lst->token == OUTPUT)
		{
			cmd->outfile = lst->word; //substring and free outfile if necessary. 
			// tmp = lst;
			// lst = lst->next;
			del_node(&lst->prev, &lst, &lst->next);
			t_lexer *tmp2 = lst;

			while (tmp2)
			{
				printf("del_node lex: %d ", tmp2->i);
				tmp2 = tmp2->next;
			}
			printf("\n");
		}
		else
			lst = lst->next;
	}
	printf("outfile: %s\n", cmd->outfile);
	return (0);
}
/**
 * @brief If cmd has heredoc-token, add it into cmd_line.   
 * 
 * Loop through cmd and if heredoc-token will be found, the node and
 * the next node, will be cut out of the lexer list and added to the
 * cmd_line t_parse struct array.
 * @param lex Tokenized input list.
 * @param eoc End of Command (index of node where cmd ends).
 * @param cmd Command struct, where the cmd infos are saved. 
 * @return int 
 */
int	handle_heredoc(t_lexer **lex, int eoc, t_parse *cmd)
{
	t_lexer *lst;

	lst = *lex;
	(void)cmd;
	while (lst && lst->i <= eoc)
	{
		if (lst->token == HEREDOC)
		{
			printf("HEREDOC: lst->i: %d lst->token: %d\n", lst->i, lst->token);
			fflush(NULL);
		}
		lst = lst->next;
	}
	return (0);
}

/**
 * @brief If cmd has cmd-token, add it into cmd_line.   
 * 
 * Loop through cmd and if cmd-token will be found, the node and
 * the next node, will be cut out of the lexer list and added to the
 * cmd_line t_parse struct array.
 * @param lex Tokenized input list.
 * @param eoc End of Command (index of node where cmd ends).
 * @param cmd Command struct, where the cmd infos are saved. 
 * @return int 
 */
int	handle_cmd(t_lexer **lex, int eoc, t_parse *cmd)
{
	t_lexer *lst;

	lst = *lex;
	(void)cmd;
	while (lst && lst->i <= eoc)
	{
		if (lst->token == WORD)
		{
			printf("CMD: lst->i: %d lst->word: %s\n", lst->i, lst->word);
			fflush(NULL);
		}
		lst = lst->next;
	}
	return (0);
}