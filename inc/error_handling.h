/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:54:44 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 14:54:45 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H
# include "minishell.h"

# define ARGC_ERR "*****Welcome to Minishell*****\n\n \
Minishell doesn't need any args"
# define MALLOC_ERR "ERROR: Malloc error detected"
# define NOENV_ERR "Sorry, env is empty. Bye"
# define ENV_ALLOC_ERR "ERROR: Nothing was extracted from envp"
# define NOTFOUND_ERR "command not found"
# define FD_ACCESS_ERR "Permission denied"
# define FD_NONEX_ERR "No such file or directory"
# define HERE_STOP_ERR "here-document delimited by end-of-file, wanted"
# define TOKEN_ERR "syntax error near unexpected token"
# define EXEC_ERR "exec error detected. try again"
# define ISDIR_ERR "Is a directory"

/*error_handling*/
int			error_msg(char *cmd, char *arg, char *msg, int ret);
int			ft_error(char *msg, t_data *data);
void		ft_parent_error(char *msg, t_data *data, t_parse *cmd);
t_status	print_warning(t_parse *cmdl, t_status err);

#endif