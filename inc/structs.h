/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubsky <rubsky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:16:58 by rubsky            #+#    #+#             */
/*   Updated: 2023/07/06 17:25:31 by rubsky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

typedef struct s_data
{
	void	*content;
	char	**envp;
	char	*input;
}	t_data;

#endif