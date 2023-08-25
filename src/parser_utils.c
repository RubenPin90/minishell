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

// void	del_node(t_lexer **n_prev, t_lexer **node, t_lexer **n_next)
// {
// 	t_lexer *tmp;

// 	tmp = *node;
// 	if (*n_prev && *n_next)
// 	{
// 		(*n_prev)->next = *n_next;
// 		(*n_next)->prev = *n_prev;
// 		*node = *n_next;
// 	}
// 	else if (*n_prev && !*n_next)
// 	{
// 		*node = *n_prev;
// 		(*n_prev)->next = NULL;
// 		*node = (*n_prev)->next;
// 	}
// 	else if (!*n_prev)
// 	{
// 		 if (*n_next)
//             (*n_next)->prev = NULL;
//         *node = *n_next;
// 	}
// 	free(tmp);
// 	tmp = NULL;
// }

/**
 * @brief Input-token is checked and copied into current cmd_line.
 * 
 * Checks input-token by opening it with read permissions only. If it can't
 * be opened, error message is printed and returned. If there is no error with
 * opening, fd is closed again. If there are more than 1 infiles in one command
 * old string is freed and new string will replace it.
 * @param cmd_line Struct of current command.
 * @param file Word at current node.
 * @return int 1 for error, 0 for SUCCESS.
 */
int	handle_infile(t_parse *cmd_line, char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (!fd)
		return (error_msg(file, FD_NONEX_ERR));
	close(fd);
	if (cmd_line->infile)
		free(cmd_line->infile);
	cmd_line->infile = ft_strdup(file);
	if (!cmd_line->infile)
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief Heredoc-token is checked and copied into current cmd_line.
 * 
 * Copies Heredoc-token into cmd_line. If there is already a heredoc
 * old string is freed and new string will replace it.
 * @param cmd_line Struct of current command.
 * @param file Word at current node.
 * @return int 1 for error, 0 for SUCCESS.
 */
int	handle_heredoc(t_parse *cmd_line, char *word)
{
	if (cmd_line->heredoc)
		free(cmd_line->heredoc);
	cmd_line->heredoc = ft_strdup(word);
	if (!cmd_line->heredoc)
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief Output-token is checked and copied into current cmd_line.
 * 
 * Checks output-token by opening it with read and write permissions. if it doesn't 
 * exist, file will be created with 777 permissions. If it can't be opened, error message 
 * is printed and returned. If there is no error with opening, fd is closed again. 
 * If there are more than 1 outfiles in one command, old string is freed and new string will replace it.
 * If type is APPEND, append bool is set to true.
 * @param cmd_line Struct of current command.
 * @param file Word at current node.
 * @return int 1 for error, 0 for SUCCESS.
 */
int	handle_outfile(t_parse *cmd_line, char *file, int type)
{
	int fd;

	if (type == APPEND)
	{
		cmd_line->append = true;
		fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	else if (type == OUTPUT)
	{
		cmd_line->append = false;
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	if (!fd)
		return (error_msg(file, FD_ACCESS_ERR));
	close(fd);
	if (cmd_line->outfile)
		free(cmd_line->outfile);
	cmd_line->outfile = ft_strdup(file);
	if (!cmd_line->outfile)
		return (FAIL);
	return (SUCCESS);
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
		if (cmd_line->heredoc)
			cmd_line->heredoc = free_null(cmd_line->heredoc);
		cmd_line++;
	}
	free(start);
	start = NULL;
	return (start);
}
