/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:17:40 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/15 10:31:12 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*REVIEW - get_main_struct_data

//		This function is a bridge between Minishell parsing part by ftersill
		or execution debug program.
*/
void	get_main_struct_data(t_exec *exec, void *data, int debug)
{
	t_debug_data	*debug_data;
	t_data			*gen;

	exec->main_struct_pointer = data;
	exec->debug = debug;
	if (debug)
	{
		debug_data = (t_debug_data *)data;
		exec->env = &debug_data->env;
		exec->env_size = &debug_data->env_size;
		exec->last_env = &debug_data->last_env;
		exec->exit_status = &debug_data->exit_status;
		*exec->exit_status = 0;
		return ;
	}
	gen = (t_data*)data;
	exec->env = &gen->env;
	exec->env_size = &gen->env_size;
	exec->last_env = &gen->last_env;
	exec->exit_status = &gen->exit_status;
	*exec->exit_status = 0;
}

/*REVIEW - close_and_reset

//		1)	Close an fd;
		2)	Sets it to zero.
*/
void	close_and_reset(int *fd)
{
	if (*fd >= 3)
		close(*fd);
	*fd = 0;
}
