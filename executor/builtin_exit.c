/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:46:54 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/15 10:30:29 by ftersill         ###   ########.fr       */
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
	// creare una funzione che faccia il free di tutto
	exec->main_struct_pointer = NULL;
	free_memory(exec);
	return (exit(exit_status), 0);
}

