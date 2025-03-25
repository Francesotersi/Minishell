/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:47:51 by alerusso          #+#    #+#             */
/*   Updated: 2025/03/25 13:46:45 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	error(int err)
{
	free_memory();
	if (err == NONE)
		return (ft_putstr_fd("Please insert an error.\n", 2), err);
	else if (err == E_ARGS)
		return (ft_putstr_fd("France non mi hai passato nulla lol\n", err), 1);
	else if (err == E_MALLOC)
		return (ft_putstr_fd("Malloc error\n", 2), err);
	return (ft_putstr_fd("UNKNOWN error\n", 2), err);
}
