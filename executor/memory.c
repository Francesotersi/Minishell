/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:37:46 by alerusso          #+#    #+#             */
/*   Updated: 2025/03/25 14:06:23 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	free_memory2(t_exec *exec);
static void	close_files(int *fds);

//REVIEW -
/*
	To update storage:	storage(data, STORE)
	TO receive storage:	storage(data, RECEIVE)
*/
t_exec	*storage(t_exec *update, int mode)
{
	static t_exec	*stack;

	if (mode == STORE)
		stack = update;
	return (stack);
}

//REVIEW - Alloc for t_exec
int	alloc_memory(t_exec **exec, int cmd_num)
{
	*exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!*exec)
		return (E_MALLOC);
	storage(*exec, STORE);
	(*exec)->fds = (int *)ft_calloc(cmd_num * 2, sizeof(int));
	if (!(*exec)->fds)
		return (E_MALLOC);
	(*exec)->commands = (char **)ft_calloc(cmd_num + 1, sizeof(char *));
	if (!(*exec)->commands)
		return (E_MALLOC);
	(*exec)->options = (char ***)ft_calloc(cmd_num + 1, sizeof(char **));
	if (!(*exec)->options)
		return (E_MALLOC);
	(*exec)->pid_list = (int *)ft_calloc(cmd_num + 1, sizeof(int));
	if (!(*exec)->pid_list)
		return (E_MALLOC);
	(*exec)->red_input = (int *)ft_calloc(cmd_num + 1, sizeof(int));
	if (!(*exec)->red_input)
		return (E_MALLOC);
	(*exec)->red_output = (int *)ft_calloc(cmd_num + 1, sizeof(int));
	if (!(*exec)->red_output)
		return (E_MALLOC);
	(*exec)->cmd_num = cmd_num;
	return (0);
}

//REVIEW - Release memory of t_exec
void	free_memory(void)
{
	t_exec	*exec;

	exec = storage(NULL, RECEIVE);
	if (!exec)
	return ;
	exec->commands = _free_matrix(exec->commands);
	exec->path = _free_matrix(exec->path);
	exec->options = _free_three_d_matrix(exec->options);
	if (exec->pid_list)
	{
		free(exec->pid_list);
		exec->pid_list = NULL;
	}
	free_memory2(exec);
	free(exec);
	storage(NULL, STORE);
}

static void	free_memory2(t_exec *exec)
{
	int	i;

	if (exec->files_to_trash)
	{
		i = -1;
		while (exec->files_to_trash[++i])
			unlink(exec->files_to_trash[i]);
	}
	exec->files_to_trash = _free_matrix(exec->files_to_trash);
	if (exec->red_input)
	{
		free(exec->red_input);
		exec->red_input = NULL;
	}
	if (exec->red_output)
	{
		free(exec->red_output);
		exec->red_input = NULL;
	}
	if (exec->fds)
	{
		close_files(exec->fds);
		free(exec->fds);
		exec->fds = NULL;
	}
}

static void	close_files(int *fds)
{
	int	i;

	i = 0;
	while (fds[i])
	{
		if (fds[i] == INT_MAX)
			close(0);
		else if (fds[i] != -1)
			close(fds[i]);
		fds[i] = -1;
		++i;
	}
}
