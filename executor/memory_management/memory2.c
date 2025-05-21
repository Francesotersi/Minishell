/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:17:40 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/21 12:19:29 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	create_empty_matrix(t_exec *exec, int cmd_num)
{
	exec->commands[cmd_num] = (char **)ft_calloc(1, sizeof(char *));
	if (!exec->commands[cmd_num])
		error(E_MALLOC, exec);
}
