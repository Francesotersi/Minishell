/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:37:46 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/28 10:23:19 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static void	free_memory2(t_exec *exec);

/*REVIEW - get_main_struct_data

//		This function is a bridge between Minishell parsing part by ftersill
		or execution debug program.
*/
void	get_main_struct_data(t_exec *exec, void *data)
{
	t_data			*gen;

	exec->main_struct_pointer = data;
	gen = (t_data *)data;
	exec->env = &gen->env;
	exec->env_size = &gen->env_size;
	exec->last_env = &gen->last_env;
	exec->exit_code = &gen->exit_code;
	exec->first_token = gen->token;
	exec->minishell_path = gen->minishell_path;
	*exec->exit_code = 0;
}

//REVIEW - Alloc for t_exec
void	alloc_memory(t_exec *exec, t_token *token, int cmd_num)
{
	exec->stdin_fd = dup(0);
	exec->stdout_fd = dup(1);
	exec->last_cmd = cmd_num;
	exec->commands = (char ***)ft_calloc(cmd_num + 2, sizeof(char **));
	if (!exec->commands)
		error(E_MALLOC, exec);
	exec->builtins = (t_builtin *)ft_calloc(BUILT_N, sizeof(t_builtin));
	if (!exec->builtins)
		error(E_MALLOC, exec);
	exec->which_cmd = (char *)ft_calloc(cmd_num + 1, sizeof(char));
	if (!exec->which_cmd)
		error(E_MALLOC, exec);
	exec->here_doc_fds = (int *)ft_calloc(cmd_num + 1, sizeof(int));
	if (!exec->here_doc_fds)
		error(E_MALLOC, exec);
	exec->pid_list = (int *)ft_calloc(cmd_num + 1, sizeof(int));
	if (!exec->pid_list)
		error(E_MALLOC, exec);
	exec->proc_sub_fds = (int *)ft_calloc(proc_sub_num(token) + 1, sizeof(int));
	if (!exec->proc_sub_fds)
		error(E_MALLOC, exec);
	exec->proc_sub_temp_fds = (int *)ft_calloc((deepest(token) \
	+ proc_sub_num(token)) * 2, sizeof(int));
	if (!exec->proc_sub_temp_fds)
		error(E_MALLOC, exec);
}

//REVIEW - Release memory of t_exec. Restores STDIN and STDOUT.
void	free_memory(t_exec *exec)
{
	if (!exec)
		return ;
	dup2(exec->stdin_fd, 0);
	dup2(exec->stdout_fd, 1);
	close(exec->stdin_fd);
	close(exec->stdout_fd);
	exec->commands = _free_three_d_matrix(exec->commands);
	exec->path = _free_matrix(exec->path);
	free(exec->builtins);
	exec->builtins = NULL;
	free(exec->pid_list);
	exec->pid_list = NULL;
	free(exec->which_cmd);
	exec->which_cmd = NULL;
	free_memory2(exec);
}

//REVIEW - 	This part is put just to be sure all junk 
//			has been trashed.
static void	free_memory2(t_exec *exec)
{
	int	i;

	i = -1;
	while (++i != exec->last_cmd)
	{
		close_and_reset(&exec->here_doc_fds[i]);
	}
	i = -1;
	while (exec->proc_sub_fds[++i])
	{
		close_and_reset(&exec->proc_sub_fds[i]);
	}
	i = -1;
	while (exec->proc_sub_temp_fds[++i])
	{
		close_and_reset(&exec->proc_sub_temp_fds[i]);
	}
	free(exec->here_doc_fds);
	exec->here_doc_fds = NULL;
	free(exec->proc_sub_fds);
	exec->proc_sub_fds = NULL;
	free(exec->proc_sub_temp_fds);
	exec->proc_sub_temp_fds = NULL;
	close_and_reset(&exec->pipe_fds[0]);
	close_and_reset(&exec->pipe_fds[1]);
}

void	create_empty_matrix(t_exec *exec, int cmd_num)
{
	exec->commands[cmd_num] = (char **)ft_calloc(1, sizeof(char *));
	if (!exec->commands[cmd_num])
		error(E_MALLOC, exec);
}
