/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:46:54 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/12 16:26:11 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//NOTE - Linea 35 SI LIBERA MEMORIA DI FRANCI
/*
//REVIEW - ft_exit

//		Operations:
		1)	We save exit status, and free everything.
		2)	We exit, with last exit status.
*/
int	ft_exit(char **args, t_exec *exec)
{
	int	exit_status;

	(void)args;
	exit_status = *exec->exit_status;
	if (exec->debug)
		free_debug_data((t_debug_data *)exec->main_struct_pointer);
	else
		(void)args;
	exec->main_struct_pointer = NULL;
	free_memory(exec);
	return (exit(exit_status), 0);
}
