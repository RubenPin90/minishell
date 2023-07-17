/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapostol <aapostol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:34:10 by aapostol          #+#    #+#             */
/*   Updated: 2023/07/17 12:42:19 by aapostol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

// reads through input string and copies every word/token into a list node
void	lexer(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		printf("%c", input[i++]);
		//test
	}
	printf("\n");
}
