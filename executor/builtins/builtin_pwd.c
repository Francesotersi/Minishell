/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:47:06 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/28 19:19:53 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
//REVIEW - ft_pwd

//		Operations:
		1)	We print getcwd string;
		2)	We free it.
*/
int	ft_pwd(char **args, t_exec *exec)
{
	char	*pwd;

	(void)args;
	*exec->exit_status = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		error(E_MALLOC, exec);
	_fd_printf(1, "%s\n", pwd);
	free(pwd);
	return (0);
}
