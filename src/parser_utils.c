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
int tkn_counter(t_lexer *lex, t_type tkn)
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
		return (1);
	close(fd);
	if (cmd_line->infile)
		free(cmd_line->infile);
	cmd_line->infile = ft_strdup(file);
	if (!cmd_line->infile)
		return (1);
	return (0);
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
		return (1);
	return (0);
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
	printf("append: %d\n", cmd_line->append);
	fd = open(file, O_RDWR | O_CREAT, 0777);
	if (!fd)
		return (1);
	close(fd);
	if (cmd_line->outfile)
		free(cmd_line->outfile);
	cmd_line->outfile = ft_strdup(file);
	if (!cmd_line->outfile)
		return (1);
	if (type == APPEND)
		cmd_line->append = true;
	else
		cmd_line->append = false;
	return (0);
}
