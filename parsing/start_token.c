/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:05:20 by ftersill          #+#    #+#             */
/*   Updated: 2025/03/21 15:09:32 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*	1)controllare che la stringa passata non sia aperta
	2)calcolare la grandezza della struttura
		attento alla divisione con le redirection
 */

int	struct_len(char *str)
{
	int	i;
	int len;

	while (str[i] != '\0')
	{
		while (str[i] != ' ' && str[i] != '\0')
			i++;
		if (str[i] == ' ')
		{
			len++;
			i++;
		}
	}
	return (len);
}

int	start_lexing(char *str)
{
	struct t_token	*token;
	int		i;

	if (open_input(str) == 1)
		return (0);
	// i = struct_len(str);
	// token = (t_token)malloc();
	// if (!token)
	// 	return (perror("malloc error"), 1);
}
