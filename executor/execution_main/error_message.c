/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:47:51 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/01 12:21:57 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	bash_message2(int message, char *file);

/*
//REVIEW - error
//
//	error prints the errore type, then free all the memory, including parsing
	part memory, and exit the whole program.
	It is called for serious problem, like malloc errors.
*/
int		error(int err, t_exec *memory)
{
	*memory->exit_status = 1;
	if (err == NONE)
	{
		ft_putstr_fd("Please insert an error.\n", 2);
	}
	else if (err == E_ARGS)
	{
		ft_putstr_fd("France non mi hai passato nulla lol\n", 2);
	}
	else if (err == E_MALLOC || err == E_FORK)
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
	else if (message == E_ENV_PARSING)
	{
		_fd_printf(2, "bash: export: `%s': not a valid identifier\n", file);
	}
	else if (message == E_CD_ARGS)
	{
		_fd_printf(2, "bash: cd: too many arguments\n");
	}
	else if (message == E_CD_NOHOME)
	{
		_fd_printf(2, "bash: cd: HOME not set\n");
	}
	else if (message == E_CMD_NOTFOUND)
	{
		_fd_printf(2, "%s: command not found\n", file);
	}
	else
		return (bash_message2(message, file));
	return (1);
}

static int	bash_message2(int message, char *file)
{
	if (message == E_EXIT_NUMERIC)
	{
		_fd_printf(2, "bash: exit: %s: numeric argument required\n", file);
	}
	else if (message == E_EXIT_NUMERIC)
	{
		_fd_printf(2, "bash: exit: too many arguments\n", file);
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
		_fd_printf(2, "ERROR MESSAGE NOT REGISTERED.\n");
	return (1);
}
