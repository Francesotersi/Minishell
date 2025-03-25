/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:06:55 by alerusso          #+#    #+#             */
/*   Updated: 2025/03/25 17:12:17 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	find_last_file(t_exec *exec, int i, t_token *token);
static int	add_one(t_exec *exec, int i, t_token *token);

int	get_file_data(t_exec *exec, t_token *token)
{
	int	i;

	i = 0;
	find_last_file(exec, i, token);
	while (token->content)
	{
		if (is_exec_sep(token->type))
		{
			++token;
			find_last_file(exec, i, token);
		}
		else if (is_red_sign(token->type))
			if (add_one(exec, i++, token) != 0)
				return (1);
		if (token->content)
			++token;
	}
	return (0);
}
