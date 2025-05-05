/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:52:40 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/04 14:59:04 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static void	prep_recursion(t_exec *exec, int fds[2], int std_out, int do_pipe);
static int	redir_output(t_exec *exec, t_token **token, bool pipe, int fds[2]);

int	manage_parenthesis(t_exec *exec, t_token **token, int getfd)
{
	pid_t	pid;//
	int		fds[2];
	int		temp_fd;
	int		redir_to_pipe;

	if (getfd)
		++(*token);
	temp_fd = exec->stdout_fd;
	redir_to_pipe = detect_pipe(*token, getfd, (*token)->prior - 1);
	int	layer = exec->prior_layer;
	prep_recursion(exec, fds, temp_fd, getfd || redir_to_pipe);
	pid = fork();//
	if (pid < 0)//
		return (close(fds[0]), close(fds[1]), error(E_FORK, exec));//
	else if (pid == 0)//
		execute_loop(*token, exec);
	if (getfd == 0)//
		exec->pid_list[(*token)->cmd_num] = pid;//
	exec->prior_layer = layer;
	exec->stdout_fd = temp_fd;
	return (dup2(temp_fd, 1), redir_output(exec, token, redir_to_pipe, fds));
}

static void	prep_recursion(t_exec *exec, int fds[2], int std_out, int do_pipe)
{
	int	i;

	i = 0;
	while (exec->proc_sub_temp_fds[i])
		++i;
	fds[0] = 0;
	fds[1] = 0;
	if (do_pipe)
	{
		pipe(fds);
		exec->stdout_fd = fds[1];
		dup2(fds[1], 1);
		exec->proc_sub_temp_fds[i++] = std_out;
		exec->proc_sub_temp_fds[i] = fds[0];
	}
	else
	{
		exec->proc_sub_temp_fds[i++] = -1;
		exec->proc_sub_temp_fds[i] = -1;
	}
}

static int	redir_output(t_exec *exec, t_token **token, bool pipe, int fds[2])
{
	int	i;

	i = 0;
	while (exec->proc_sub_temp_fds[i])
		++i;
	exec->proc_sub_temp_fds[--i] = 0;
	exec->proc_sub_temp_fds[--i] = 0;
	close(1);
	close(fds[1]);
	if (pipe == 1)
	{
		close_and_reset(&exec->pipe_fds[0]);
		exec->pipe_fds[0] = fds[0];
	}
	skip_deeper_layers(token, exec->prior_layer);
	if ((*token)->type == AND || (*token)->type == OR)
		goto_valid_block(exec, token);
	if ((*token)->type == AND || (*token)->type == OR)
		wait_everyone(exec);
	if ((*token)->content)
		++(*token);
	return (fds[0]);
}

int	get_subshell_filename(t_exec *exec, t_token **token, int cmd_num)
{
	int		pipe_fd;
	int		argv_index;
	char	*filename;
	char	*temp;
	t_token	*current_token;

	current_token = *token;
	pipe_fd = manage_parenthesis(exec, token, _YES);
	if (pipe_fd <= 0)
		error(E_OPEN, exec);
	temp = ft_itoa(pipe_fd);
	if (!temp)
		return (close(pipe_fd), error(E_MALLOC, exec));
	filename = ft_strjoin("/dev/fd/", temp);
	if (!filename)
		return (close(pipe_fd), free(temp), error(E_MALLOC, exec));
	argv_index = find_command_argument_index(exec, current_token);
	if (argv_index <= 0)
	{
		bash_message(E_PERMISSION_DENIED, filename);
		return (close(pipe_fd), free(temp), free(filename), 1);
	}
	free(exec->commands[cmd_num][argv_index]);
	exec->commands[cmd_num][argv_index] = filename;
	return (save_process_substitution_fd(exec, pipe_fd), free(temp), 0);
}
