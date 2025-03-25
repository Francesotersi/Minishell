/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:43:26 by alerusso          #+#    #+#             */
/*   Updated: 2025/03/25 14:08:24 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execute(t_token *tokens)
{
	t_exec	*exec;

	if (!tokens)
		error(E_ARGS);
	if (alloc_memory(&exec, count_commands(tokens)) != 0)
		return (error(E_MALLOC));
	
	free_memory();
	return (0);
}
