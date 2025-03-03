/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:13:23 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/11 16:55:44 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

extern int	g_signum;

/*executor*/
int		exec_child(t_data *data, t_parse *cmd, char *cmdpath);
int		exec_builtin(t_data *data, t_parse *cmd, bool parent);
int		exec_single_cmd(t_parse *cmd, bool parent, t_data *data);
int		exec_multi_cmds(t_parse *cmd_line, int cmds, t_data *data);
int		executor(t_data *data);

/*exec_utils*/
int		create_pipes(t_parse *cmd_line, int cmds);
int		ft_dup2(int fdin, int fdout);
void	fdmulti_redef(t_parse *cmd, int *tmp_fdout, int *tmp_fdin, int cmds);
void	replace_fdmulti(t_data *data, t_parse *cmd);
void	replace_fd(t_data *data, t_parse *cmd);

/*exec_heredoc*/
int		handle_heredoc(t_data *data, t_parse *cmd_line);
void	heredoc_name(t_data *data, t_parse *cmd);
int		find_heredoc(t_data *data, t_parse *cmd, t_lexer *redir);
int		heredocfun(t_data *data, t_parse *cmd, char *delim, int type);
int		cleanup_herefun(char **str, int *fd, int ret);

/*exec_cmdfinder*/
int		check_access(t_data *data, t_parse *cmdl, char *cmdn, char **cmdp);
int		check_dir(t_parse *cmdl, char *cmdname);
int		is_binary(t_data *data, t_parse *cmdl, char **cmdpath, char *cmdname);
int		cmdfinder(t_data *data, t_parse *cmd_line);
int		find_cmd(t_parse *cmdl, char *cmdname, char **cmdpath, t_data *data);

/*exec_fds*/
int		handle_fds(t_parse *cmd);
int		handle_infile(t_parse *cmd, t_lexer *redir);
int		handle_outfile(t_parse *cmd_line, t_lexer *redir);
int		ft_access_wrapper(t_parse *cmdl, char *cmdname);

/*exec_fd_utils*/
int		cleanup_fd(int *fd);
int		update_fd(t_parse *cmd, char **name);
int		ft_open(char *file, t_type token, char *heredoc);
int		close_all_fds(t_parse *cmd_line);
int		switch_stdfd(t_data *data, t_parse *cmd, int *stdfd, bool switch_fd);

/*exec_exstatus*/
void	ft_waitpid(t_data *data, t_parse *cmd);
void	check_status(int status, int *excode);
int		set_exstat(t_parse *cmd_line, bool *execute, int status);

#endif