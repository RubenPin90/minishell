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
	t_lexer *tmp;
	// bool	check;

	lst = *lex;
	printf("eoc: %d\n", eoc);
	while (lst && lst->i <= eoc)
	{
		printf("REDIR: lst->i: %d lst->token: %d\n", lst->i, lst->token);
		// check = true;
		if (lst->token == INPUT)
		{
			// check = false;	
			cmd->infile = lst->word;	
			tmp = lst->prev;
			if (tmp && lst->next)
			{
				tmp->next = lst->next;
				lst->next->prev = tmp;
			}
			else if (tmp && !lst->next)
				tmp->next = NULL;
			else if (tmp == NULL)
			{
				tmp = lst->next;
				tmp->prev = NULL;
			}
			free(lst);
			lst = tmp;
		}
		lst = lst->next;
	}
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