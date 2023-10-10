/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:06:58 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 14:06:59 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

/*parser*/
bool	ft_push_redir(t_lexer **a, t_lexer **b, bool check);
int		init_cmd(t_lexer *cmd_list, t_parse *current_cmd);
int		extract_cmd(t_data *data, t_lexer **lst, t_parse *cmd_line, char **cmd);
void	set_ids(t_parse *cmd_line, int len);
int		parser(t_data *data, t_lexer *lst);

#endif