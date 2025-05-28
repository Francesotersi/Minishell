/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:47:06 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/28 10:19:44 by ftersill         ###   ########.fr       */
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
	set_exit_code(exec, 0);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		error(E_MALLOC, exec);
	_fd_printf(1, "%s\n", pwd);
	free(pwd);
	return (0);
}
