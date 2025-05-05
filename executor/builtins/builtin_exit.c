/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:46:54 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/05 15:24:15 by ftersill         ###   ########.fr       */
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
	int	exit_code;

	if (exec->at_least_one_pipe)
		return (set_exit_code(exec, 0), 0);
	if (exec->prior_layer == 0)
		_fd_printf(2, "exit\n");
	if (check_args(args, exec))
		return (0);
	exit_code = *exec->exit_code;
	if (exec->debug)
		free_debug_data((t_debug_data *)exec->main_struct_pointer);
	else
		(void)args;
	// creare una funzione che faccia il free di tutto
	exec->main_struct_pointer = NULL;
	free_memory(exec);
	return (exit(exit_code), 0);
}

static int	check_args(char **args, t_exec *exec)
{
	int	len;

	*exec->exit_code = 0;
	if (!args[1])
		return (0);
	len = _sub_strlen(args[1], "0123456789", INCL);
	if (args[1][len] != 0)
		return (bash_message(E_EXIT_NUMERIC, args[1]), 0);
	if (args[2])
		return (bash_message(E_EXIT_ARGS, NULL), 1);
	*exec->exit_code = ft_atoi(args[1]);
	return (0);
}

int	exit_process(t_exec *exec)
{
	int	exit_code;

	exit_code = *exec->exit_code;
	if (exec->debug)
		free_debug_data((t_debug_data *)exec->main_struct_pointer);
	// creare una funzione che faccia il free di tutto
	exec->main_struct_pointer = NULL;
	free_memory(exec);
	return (exit(exit_code), 0);
}
