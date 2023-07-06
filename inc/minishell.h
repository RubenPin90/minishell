/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapostol <aapostol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:31:11 by rubsky            #+#    #+#             */
/*   Updated: 2023/07/06 18:59:25 by aapostol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include "structs.h"
# include <libft.h>

/*signals*/
void	handle_signals(struct sigaction sigact);
void	receive_signal(int signum, siginfo_t *info, void *context);

/*input*/
int		handle_input(t_data *data);

/*utils*/
char	**copy_envp(char **env_org);


#endif