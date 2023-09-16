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
 * @param end
 * @return int Number of token.
 */
int tkn_counter(t_lexer *lex, t_type tkn, t_type end)
{
	int count;

	count = 0;
	while (lex && lex->token != end)
	{
		if (lex->token == tkn)
			count++;
		lex = lex->next;
	}
	return (count);
}



/**
 * @brief Destroy function of t_parse array. 
 * 
 * Checks if argument exists else returns NULL. Sets new pointer start
 * at the beginning of the array. Loops through the array and in each
 * index all 2D arrays and strings are freed. Afterwards start is freed 
 * and is set to NULL.
 * @param cmd_line T_parse array of structs.
 * @return t_parse* pointer pointing to NULL or directly NULL.
 */
t_parse *free_parser(t_parse *cmd_line)
{
	t_parse *start;

	start = cmd_line;	
	while (cmd_line->id != 0)
	{
		if (cmd_line->cmd)
			cmd_line->cmd = free_arr(cmd_line->cmd);
		if (cmd_line->infile)
			cmd_line->infile = free_null(cmd_line->infile);
		if (cmd_line->outfile)
			cmd_line->outfile = free_null(cmd_line->outfile);
		if (cmd_line->redir)
			free_lexer(&cmd_line->redir);
		cmd_line++;
	}
	free(start);
	start = NULL;
	return (start);
}
