/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapostol <aapostol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:35:53 by aapostol          #+#    #+#             */
/*   Updated: 2023/07/14 16:41:50 by aapostol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

// lexer.c
void	lexer(char *input);

// lexer_utils.c
t_lexer	*new_lexer_node(char *word, int token);
void	lexer_addback(t_lexer **lst, t_lexer *new);

#endif