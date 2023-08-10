/**
 * @file parser.c
 * @brief Functions initalizing and creating the parser.
 */

#include "parser.h"

/**
 * @brief  
 * 
 * @param lst_head 
 * @param eoc 
 * @param cmd 
 * @return int 
 */
int	extract_cmd(t_lexer **lst_head, int eoc, t_parse *cmd)
{
	if (handle_redir(lst_head, eoc, cmd))
		return (1);
	// if (handle_heredoc(lst_head, eoc, cmd))
	// 	return (1);
	// if (handle_cmd(lst_head, eoc, cmd))
	// 	return (1);
	return (0);
}
/**
 * @brief Convertes lexer list to each command. 
 * 
 * Callocs an array of t_parse size of number of commands.
 * Loops through the lexer linked list until it finds a '|' or NULL
 * in the next node. Calls extract_cmd to do the necessary steps to
 * extract the important infos of that cmd.
 * @param data General data struct.
 * @param lex Tokenized input list.
 * @param cmd_line Struct array of cmds.
 * @return int 1 if error; 0 if success
*/
int	parser(t_data *data, t_lexer *lex, t_parse **cmd_line)
{
	t_lexer	*start;
	int		cmd_id;

	data->cmds = tkn_counter(lex, PIPE) + 1;
	printf("data->cmds: %d\n", data->cmds);
	*cmd_line = ft_calloc(data->cmds, sizeof(t_parse));
	if (!*cmd_line)
		return (1);
	start = lex;
	cmd_id = 0;
	while (lex)
	{
		if (lex->next == NULL || lex->next->token == PIPE)
		{
			if (extract_cmd(&start, lex->i, cmd_line[cmd_id]))
				return (1);
			if (cmd_id++ < data->cmds - 1)
			{
				start = lex->next->next;
				if (start)
					lex = start;
			}
			else
				break ;
		}
		else
			lex = lex->next;
		printf("cmd_line->infile: %s\n", (*cmd_line)->infile);
	}
	return (0);
}
