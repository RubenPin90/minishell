/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubsky <rubsky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:46:55 by rubsky            #+#    #+#             */
/*   Updated: 2023/07/06 17:25:17 by rubsky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input(t_data *data)
{
	data->input = readline("> ");
	if (!data->input)
		return (1);
	printf("You wrote: %s\n", data->input);
	return (0);
}
