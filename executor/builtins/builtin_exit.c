/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:46:54 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/28 10:44:52 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	check_args(char **args, t_exec *exec);

/*
//REVIEW - ft_exit

//		Operations:
		1)	We save exit status, and free everything;
		2)	In check_args:
		- 	we check if args[1] is a number;
		- 	we check if there are more than 2 args;
		- 	we change *exec->exit_code;
		3)	We exit, with args[1] exit code.
*/
int	ft_exit(char **args, t_exec *exec)
{
	unsigned char	exit_code;

	set_exit_code(exec, 0);
	if (check_args(args, exec) || exec->at_least_one_pipe)
		return (0);
	if (exec->prior_layer == 0)
		_fd_printf(2, "exit\n");
	exit_code = *exec->exit_code;
	free(exec->minishell_path);
	free_all(exec->first_token, exec->main_struct_pointer, false);
	_free_matrix(*exec->env);
	exec->main_struct_pointer = NULL;
	free_memory(exec);
	close(0);
	close(1);
	close(2);
	return (exit(exit_code), 0);
}

/*
//REVIEW - check_args

//		Operations:
		1)	With no args, we return exit code 0;
		2)	If args[1] is not a number, we set exit code 2, then we exit.
			This check is done with overflow_check;
		3)	If there are more than 2 args, we set exit code 1, 
			then we do not exit;
		4)	We set exit code to args[1] with ft_atoi.
*/
static int	check_args(char **args, t_exec *exec)
{
	set_exit_code(exec, 0);
	if (!args[1])
		return (0);
	else if (overflow_check(args[1], LLONG_MAX, LLONG_MIN, 0) == _YES)
	{
		set_exit_code(exec, 2);
		return (bash_message(E_EXIT_NUMERIC, args[1]), 0);
	}
	else if (args[2])
	{
		set_exit_code(exec, 1);
		return (bash_message(E_EXIT_ARGS, NULL), 1);
	}
	set_exit_code(exec, ft_atoi(args[1]));
	return (0);
}

/*
//REVIEW - exit_process

//		An internal ft_exit, that does not take arguments.
		Used to exit from parenthesis processes and for edge
		cases like malloc or fork errors.
*/
int	exit_process(t_exec *exec)
{
	int	exit_code;

	exit_code = *exec->exit_code;
	free(exec->minishell_path);
	free_all(exec->first_token, exec->main_struct_pointer, false);
	_free_matrix(*exec->env);
	exec->main_struct_pointer = NULL;
	free_memory(exec);
	close(0);
	close(1);
	close(2);
	return (exit(exit_code), 0);
}
