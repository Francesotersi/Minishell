/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:46:57 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/28 19:19:40 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static void	print_env(char **env);
static int	what_file_is(t_exec *exec, char *arg);

/*
//REVIEW - print_env

//		If there are no arguments, calls print_env.
*/
int	ft_env(char **args, t_exec *exec)
{
	if (args[1])
		return (what_file_is(exec, args[1]));
	*exec->exit_status = 0;
	print_env(*exec->env);
	return (0);
}

/*
//REVIEW - print_env

//		For every characters of the environment, if they have '=',
		we print them.
*/
static void	print_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			_fd_printf(1, "%s\n", env[i]);
		++i;
	}
}

/*
//REVIEW - what_file_is

//		ft_env, for subject request, must not allow any arguments.
		Else, must fail, and set the right error status.
		Like shell:
		-	If is a directory: 	Exit status set to 126;
		-	If is not a file:	Exit status set to 127;
		-	If it were an executable, we would need to execute it.
			However, since Minishell subject specify NO ARGUMENTS
			for env:			Exit status set to 127;
		-	In other cases:		Exit status set to 126.  
*/
static int	what_file_is(t_exec *exec, char *arg)
{
	DIR	*dir;

	dir = opendir(arg);
	if (dir)
	{
		_fd_printf(2, "env: %s: Is a directory\n", arg);
		closedir(dir);
		return (set_exit_status(exec, 126));
	}
	else if (access(arg, F_OK) != 0)
	{
		_fd_printf(2, "env: %s: No such file or directory\n");
		return (set_exit_status(exec, 127));
	}
	else if (access(arg, F_OK | X_OK) != 0)
	{
		_fd_printf(2, "env: %s: Cannot execute for Minishell subject\n");
		return (set_exit_status(exec, 127));
	}
	_fd_printf(2, "env: %s: permission denied\n");
	return (set_exit_status(exec, 126));
}
