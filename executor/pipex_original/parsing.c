/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:25:11 by alerusso          #+#    #+#             */
/*   Updated: 2025/03/25 14:27:29 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	get_env_path(char *env[], t_exec *exec);
static int	check_one(char **command, t_exec *exec);
static int	get_filenames(char *argv[], t_exec *exec);
int			get_commands_recursion(char *argv[], t_exec *exec, int i);

/*
	List of stuff to do:

	1)	get the filenames, and consider here_doc if BONUS is ON;
	2)	get the path from the environment matrix env;
	3)	get the commands: it means modifying argv and check if is a valid path.
		If even ONE command does not exist, everything is aborted;
	4)	get the options of every command.
*/
int	get_data(t_token *tokens, char *env[], t_exec *exec)
{
	int		err;
	int		i;
	char	**temp_path;
	char	**temp_cmd;

	err = get_filenames(tokens, exec);
	if (err != 0)
		return (err);
	err = get_env_path(env, exec);
	if (err != 0)
		return (err);
	temp_path = exec->path;
	temp_cmd = exec->commands;
	i = 2 + exec->here_doc_bool;
	err = get_commands(tokens, exec, i);
	exec->path = temp_path;
	exec->commands = temp_cmd;
	if (err != 0)
		return (err);
	err = get_options(exec);
	if (err != 0)
		return (err);
	return (0);
}

/*
	ft_strlen has a + 1 because of \0.
*/
static int	get_filenames(t_token *tokens, t_exec *exec)
{
	int	len;
	int	err;

	if ((set->switch_1_bonus == ON) && \
	(ft_strncmp(argv[1], "here_doc", 8) == 0))
	{
		err = get_here_doc_file(argv, exec);
		if (err != 0)
			return (err);
	}
	else
	{
		len = ft_strlen(argv[1]) + 1;
		exec->infile = (char *)ft_calloc(len, sizeof(char));
		if (!exec->infile)
			return (ER_MALLOC);
		ft_strlcpy(exec->infile, argv[1], len);
	}
	if (get_second_filename(argv, exec) != 0)
		return (ER_MALLOC);
	return (0);
}

/*
	1)	Find the PATH if exists;
	2)	Split it with :;
*/
int	get_env_path(char *env[], t_exec *exec)
{
	int	i;

	i = 0;
	while ((env[i]) && (ft_strncmp(env[i], "PATH=", 5) != 0))
	{
		++i;
	}
	if (!env[i])
		return (ER_NOPATH);
	exec->path = ft_split(env[i], ':');
	if (!exec->path)
		return (ER_MALLOC);
	return (0);
}

/*
	This is more complicated.

	1)	Starting from index 2 (argv[0] = exec, argv[1] = infile), or from
		index 3 if there is the here_doc file;
	WHILE LOOP:

		2)	if the current path ha not a '/', add it. else, strdup it;
		3)	If we strjoin a path (ex: /usr/bin/) and add the command (ex: grep)
			we get /usr/bin/grep, the final program path;
		4)	If check one finds that the program in the path exists, it 
			reset the exec->path matrix, increase the command index, and
			the current command we are actually saving.
			If index, after the increase, happens to be equal to the
			start value of index (2 + here_doc_bool), stop.
		
		If, after have seen the entire path, it does not have found
		any program, it perform a strdup of "error!", increase i,
		reset the path and recall recursively get_commands.
*/
int	get_commands(char *argv[], t_exec *exec, int i)
{
	char	**start_path;

	start_path = exec->path;
	while (*exec->path)
	{
		if ((*exec->path)[ft_strlen(*exec->path) - 1] != '/')
			*exec->commands = ft_strjoin("/", argv[i]);
		else
			*exec->commands = ft_strdup(argv[i]);
		exec->temp = *exec->commands;
		*exec->commands = ft_strjoin(*exec->path, exec->temp);
		if (!*exec->commands)
			return (ER_MALLOC);
		if (check_one(exec->commands, exec) == 0)
		{
			exec->path = start_path;
			if (++i == exec->cmd_num + 2 + exec->here_doc_bool)
				return (0);
			exec->commands++;
		}
		exec->path++;
	}
	exec->path = start_path;
	*exec->commands = ft_strdup("error!");
	return (get_commands_recursion(argv, exec, ++i));
}

/*
	1)	We calculate the strlen of the command until we find a SPACE:
		because we have to consider the options (ex: wc -l);
	2)	We save a temp copy of the command, until we found \0 or SPACE;
	3)	We access the file. If it exists, we return 0, else 1.

	If a malloc fails here, we go on. 
	Get_commands will fail anyway soon, and will abort the execution.
*/
int	check_one(char **command, t_exec *exec)
{
	int	len;
	int	i;

	free(exec->temp);
	len = _sub_strlen(*command, " ", EXCL);
	exec->temp = (char *)ft_calloc(len + 2, sizeof(char));
	if (!exec->temp)
		return (free(*command), 1);
	i = 0;
	while (((*command)[i]) && ((*command)[i] != ' '))
	{
		exec->temp[i] = (*command)[i];
		++i;
	}
	if (access(exec->temp, F_OK | X_OK) == 0)
		return (free(exec->temp), 0);
	free(*command);
	free(exec->temp);
	exec->temp = NULL;
	*command = NULL;
	return (1);
}
