/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:17:40 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/28 19:22:32 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

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
