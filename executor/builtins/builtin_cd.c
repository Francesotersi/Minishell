/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:47:01 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/28 19:19:35 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	up_env(char **update, char *old_pwd, char *pwd, t_exec *exec);
static void	back_to_home(char **env, char **new_dir);

/*REVIEW - ft_cd

//		Cd is a program that takes ONLY one argument.

//		If there are no arguments, it does nothing, and returns ES 0.
		Same if there are more than one arguments, but returns ES 1..

//		Basically, the cd program does three operations:
			Update the environment variable OLDPWD with getcwd;
		 	change the current directory with chdir;
			Update the environment variable PWD with getcwd.
		The environment changes must be apply only if the calls of
		getcwd and chdir are successful.
		To apply the environment changes, we call ft_export.

//		Operations:
		1)	Check for args size. If more than one arguments, ES 1.
			If less than one, ES 0;
		2)	We get old_pwd, we change the directory, we get pwd;
		3)	We alloc a matrix (pwd_update), that will store the data
			to pass to ft_export (to update OLD_PWD and PWD);
		4)	We call up_env. Go below.
*/
int	ft_cd(char **args, t_exec *exec)
{
	char	*old_pwd;
	char	*pwd;
	char	**pwd_update;
	char	*new_dir;

	*exec->exit_status = 0;
	if (args[1] && args[2])
		return (bash_message(E_CD_ARGS, NULL), set_exit_status(exec, 1));
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		error(E_MALLOC, exec);
	new_dir = args[1];
	if (!args[1])
		back_to_home(*exec->env, &new_dir);
	if (chdir(new_dir) != 0)
		return (free(old_pwd), set_exit_status(exec, 1));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(old_pwd), error(E_MALLOC, exec));
	pwd_update = (char **)ft_calloc(3, sizeof(char *));
	if (!pwd_update)
		return (free(old_pwd), free(pwd), error(E_MALLOC, exec));
	pwd_update[0] = NULL;
	up_env(pwd_update, old_pwd, pwd, exec);
	return (0);
}

/*REVIEW - back_to_home

//	cd without arguments change current directory to $HOME (from env).		
	If $HOME is unsetted, bash prints a unique message.
*/
static void	back_to_home(char **env, char **new_dir)
{
	*new_dir = ft_getenv(env, "HOME", NULL);
	if (!*new_dir)
	{
		bash_message(E_CD_NOHOME, NULL);
		return ;
	}
	while (**new_dir && **new_dir != '=')
		++(*new_dir);
	if (**new_dir == '=')
		++(*new_dir);
}

/*REVIEW - update_environment

//		1)	We strjoin PWD= and the current pwd: ft_export mimics the
			real export, so it understand this syntax;
		2)	We call ft_export, and we free the str;
		3)	Same for OLDPWD. Lastly, we free the update matrix.
*/
static int	up_env(char **update, char *old_pwd, char *pwd, t_exec *exec)
{
	char	*str;

	str = ft_strjoin("PWD=", pwd);
	if (!str)
		return (free(old_pwd), free(pwd), free(update), error(E_MALLOC, exec));
	update[1] = str;
	ft_export(update, exec);
	free(str);
	str = ft_strjoin("OLDPWD=", old_pwd);
	if (!str)
		return (free(old_pwd), free(pwd), free(update), error(E_MALLOC, exec));
	update[1] = str;
	ft_export(update, exec);
	free(str);
	free(update);
	free(old_pwd);
	free(pwd);
	return (0);
}
