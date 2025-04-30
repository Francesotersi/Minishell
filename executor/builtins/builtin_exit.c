/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:46:54 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/28 19:19:43 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	check_args(char **args, t_exec *exec);

//NOTE - Linea 36 SI LIBERA MEMORIA DI FRANCI
/*
//REVIEW - ft_exit

//		Operations:
		1)	We save exit status, and free everything.
		2)	We exit, with last exit status.
*/
int	ft_exit(char **args, t_exec *exec)
{
	int	exit_status;

	if (exec->prior_layer == 0)
		_fd_printf(2, "exit\n");
	if (check_args(args, exec))
		return (0);
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

static int	check_args(char **args, t_exec *exec)
{
	int	len;

	*exec->exit_status = 0;
	if (!args[1])
		return (0);
	len = _sub_strlen(args[1], "0123456789", INCL);
	if (args[1][len] != 0)
		return (bash_message(E_EXIT_NUMERIC, args[1]), 0);
	if (args[2])
		return (bash_message(E_EXIT_ARGS, NULL), 1);
	*exec->exit_status = ft_atoi(args[1]);
	return (0);
}

int	exit_process(t_exec *exec)
{
	int	exit_status;

	exit_status = *exec->exit_status;
	if (exec->debug)
		free_debug_data((t_debug_data *)exec->main_struct_pointer);
	// creare una funzione che faccia il free di tutto
	exec->main_struct_pointer = NULL;
	free_memory(exec);
	return (exit(exit_status), 0);
}
