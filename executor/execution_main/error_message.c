/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:47:51 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/27 16:08:01 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	bash_message2(int message, char *file);
static int	bash_message3(int message, char *file);
static int	bash_message4(int message, char *file);

/*
//REVIEW - error
//
//	error prints the errore type, then free all the memory, including parsing
	part memory, and exit the whole program.
	It is called for serious problem, like malloc errors.
*/
int	error(int err, t_exec *memory)
{
	*memory->exit_code = 1;
	if (err == NONE)
	{
		ft_putstr_fd("Please insert an error.\n", 2);
	}
	else if (err == E_MALLOC)
	{
		ft_putstr_fd("bash: Cannot allocate memory\n", 2);
	}
	else if (err == E_FORK)
	{
		ft_putstr_fd("bash: fork: Cannot allocate memory\n", 2);
	}
	else if (err == E_OPEN)
	{
		ft_putstr_fd("Open critical error\n", 2);
	}
	else
	{
		ft_putstr_fd("ERROR MESSAGE NOT REGISTERED.\n", 2);
	}
	return (exit_process(memory));
}

/*
//REVIEW - bash_message

//	bash_message prints the error type, showing, in some cases,
	what file cause the error.
	It just prints the error, though: it does not kill the process.
*/
int	bash_message(int message, char *file)
{
	if (message == E_OPEN)
	{
		_fd_printf(2, "bash: %s: No such file or directory\n", file);
	}
	else if (message == E_EXPORT_PARSING)
	{
		_fd_printf(2, "bash: export: `%s': not a valid identifier\n", file);
	}
	else if (message == E_UNSET_PARSING)
	{
		_fd_printf(2, "bash: unset: `%s': not a valid identifier\n", file);
	}
	else if (message == E_CD)
	{
		_fd_printf(2, "bash: cd: %s: No such file or directory\n", file);
	}
	else if (message == E_CD_ARGS)
	{
		_fd_printf(2, "bash: cd: too many arguments\n");
	}
	else
		return (bash_message2(message, file));
	return (1);
}

static int	bash_message2(int message, char *file)
{
	if (message == E_CD_ENV)
	{
		_fd_printf(2, "bash: cd: %s not set\n", file);
	}
	else if (message == E_EXIT_NUMERIC)
	{
		_fd_printf(2, "bash: exit: %s: numeric argument required\n", file);
	}
	else if (message == E_EXIT_ARGS)
	{
		_fd_printf(2, "bash: exit: too many arguments\n", file);
	}
	else if (message == E_ENV_DIRECTORY)
	{
		_fd_printf(2, "bash: %s: Is a directory\n", file);
	}
	else if (message == E_ENV_NOTFOUND)
	{
		_fd_printf(2, "bash: %s: No such file or directory\n", file);
	}
	else
		return (bash_message3(message, file));
	return (1);
}

static int	bash_message3(int message, char *file)
{
	if (message == E_ENV_EXE)
	{
		_fd_printf(2, "bash: %s: It's a file with execute perm.\n", file);
	}
	else if (message == E_ENV_PERMISSION)
	{
		_fd_printf(2, "bash: %s: Permission denied\n", file);
	}
	else if (message == E_CMD_NOTFOUND)
	{
		_fd_printf(2, "%s: command not found\n", file);
	}
	else if (message == E_IS_DIRECTORY)
	{
		_fd_printf(2, "bash: %s: Is a directory\n", file);
	}
	else if (message == E_PERMISSION_DENIED)
	{
		_fd_printf(2, "bash: %s: Permission denied\n", file);
	}
	else
		return (bash_message4(message, file));
	return (1);
}

static int	bash_message4(int message, char *file)
{
	if (message == E_HEREDOC_CTRL_D)
	{
		_fd_printf(2, "bash: warning: here-doc delimited by end-of-file\n");
	}
	else if (message == E_NOFILE)
	{
		_fd_printf(2, "bash: %s: No such file or directory\n", file);
	}
	else if (message == E_PROC_SUB)
	{
		_fd_printf(2, "process substitution must be: \n1)\twith a command;\n2");
		_fd_printf(2, ")\tin the same layer of command;\n3)\tafter command.\n");
		_fd_printf(2, "\nWrong example are:\n1)\t<(ls);\n2)\t(cat) <(ls);");
		_fd_printf(2, "\n3)\t<(ls) echo.\n");
	}
	else
		_fd_printf(2, "ERROR MESSAGE NOT REGISTERED.\n");
	return (1);
}
