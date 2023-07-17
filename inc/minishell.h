/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapostol <aapostol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:31:11 by rpinchas          #+#    #+#             */
/*   Updated: 2023/07/14 16:05:34 by aapostol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <libft.h>
# include "structs.h"
# include "lexer.h"

/*signals*/
void	handle_signals();
void	receive_signal(int signum, siginfo_t *info, void *context);

/*input*/
int		handle_input(t_data *data);

/*utils*/
char	**copy_envp(char **env_org);

#endif