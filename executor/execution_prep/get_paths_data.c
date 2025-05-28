/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:37:40 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/28 10:32:45 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	get_one(t_exec *exec, char **command, char **path);
static int	_add_sign_left(char **string, char sign);

/*REVIEW - get_paths_data

//		1)	We get PATH from the environment, with ft_getenv;
		2)	If the PATH does not exits, some moron has unsetted it.
			Bash, in this case, just run the command as it is.
			So, for example, if there is a command named "ls" in our working
			directory, bash will still be able to execute it.
			So, we do the same: we just pretend anything happened, and that
			everything is fine.
			Live like bash. You'll live better;
		3)	We split the PATH with ft_split, using ':' as parameter;
		4)	We iterate through every command stored in the matrix of argv;
		5)	If the file is NOT a builtin and is not already a valid executable
			(/bin/grep is already a valid executable), get it. 
*/
int	get_paths_data(t_exec *exec)
{
	char	*path;
	int		cmd_index;

	path = get_env(*exec->env, "PATH");
	if (!path)
		return (0);
	exec->path = ft_split(path, ':');
	if (!exec->path)
		error(E_MALLOC, exec);
	cmd_index = 0;
	while (exec->commands[cmd_index])
	{
		if ((*exec->commands[cmd_index] && \
			*exec->commands[cmd_index][0] != '\0') && \
			exec->which_cmd[cmd_index] == _NO && \
			access(*exec->commands[cmd_index], X_OK))
		{
			get_one(exec, exec->commands[cmd_index], exec->path);
		}
		++cmd_index;
	}
	return (0);
}

/*REVIEW - get_one

//		1)	 Add a '/' sign left to the command ("ls" becomes "/ls");
		2)	We iterate for every possible path;
		3)	We strjoin the path with the command;
		4)	We use access to see if the file in that path is a valid
			executable. If it is, we free the old command, set the new
			path as argv[0];
		5)	Else, we free the current strjoined string, and we continue;
		6)	In case of failure, next checks will prevent execve from being
			launched for that command block.
*/
static int	get_one(t_exec *exec, char **command, char **path)
{
	char	*temp;
	int		i;

	if (!command || !command[0])
		return (0);
	i = 0;
	if (_add_sign_left(command, '/') != 0)
		error(E_MALLOC, exec);
	while (path[i])
	{
		temp = ft_strjoin(path[i], *command);
		if (!temp)
			error(E_MALLOC, exec);
		if (access(temp, X_OK) == 0)
		{
			free(*command);
			*command = temp;
			break ;
		}
		free(temp);
		i++;
	}
	return (0);
}

// 	I have to reallocate the entire fucking string
//	to put a fucking '/'
//	calm down Ale calm down
//	It's all ok
//	Just string management
//	Nothing to worry about chill
/*REVIEW - _add_sign_left

//		Add a sign left in a string.
		String is reallocated.
*/
static int	_add_sign_left(char **string, char sign)
{
	size_t	len;
	char	*new_string;

	if ((!string) || (!*string))
		return (1);
	len = ft_strlen(*string);
	new_string = (char *)ft_calloc(len + 2, sizeof(char));
	if (!new_string)
		return (1);
	new_string[0] = sign;
	ft_strlcpy(new_string + 1, *string, len + 1);
	free(*string);
	*string = new_string;
	return (0);
}
