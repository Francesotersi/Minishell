/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_generic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:04:20 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/01 12:53:20 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	bigger(int n1, int n2)
{
	return (n1 * (n1 >= n2) + n2 * (n1 < n2));
}

/*REVIEW - set_exit_status

//	Set exit status. Returns it.
*/
int	set_exit_status(t_exec *exec, int exit_status)
{
	*exec->exit_status = exit_status;
	return (exit_status);
}

/*
//REVIEW - is_a_valid_executable

	This function is launched before command execution.
	It checks the executability of the program, and prints a bash_message if:

	1)	The executable is a directory 	(Exit status 126);
	2)	There executable does not exist (Exit status 127).
*/
int	is_a_valid_executable(t_exec *exec, int i)
{
	DIR	*dir;

	if (exec->which_cmd[i] != 0)
		return (_YES);
	if (!exec->commands[i][0])
		return (_NO);
	dir = opendir(exec->commands[i][0]);
	if (dir)
	{
		bash_message(E_IS_DIRECTORY, exec->commands[i][0]);
		closedir(dir);
		set_exit_status(exec, 126);
		return (_NO);
	}
	else if (access(exec->commands[i][0], F_OK | X_OK) != 0)
	{
		bash_message(E_CMD_NOTFOUND, exec->commands[i][0]);
		set_exit_status(exec, 127);
		return (_NO);
	}
	return (_YES);
}

void	write_here_doc(char *line, t_exec *exec, int fd)
{
	int		i;
	int		end;
	char	*env_str;
	char	temp;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			end = i + 1;
			while (line[end] && line[end] != ' ' && line[end] != '$')
				++end;
			temp = line[end];
			line[end] = 0;
			env_str = ft_getenv(*exec->env, line + i + 1, NULL);
			if (env_str)
				ft_putstr_fd(env_str, fd);
			if (!temp)
				break ;
			line[end] = temp;
			i = end - 1;
		}
		else
			write(fd, &line[i], 1);
	}
}
