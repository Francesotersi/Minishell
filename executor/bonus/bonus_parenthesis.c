/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:52:40 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/13 08:43:11 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	prep_recursion(t_exec *exec, int fds[2], int std_out, int do_pipe);
static int	redir_output(t_exec *exec, t_token **token, bool _pipe, int fds[2]);
static int	filedata_after_parenthesis(t_exec *exec, t_token *token);

int	manage_parenthesis(t_exec *exec, t_token **token, int getfd)
{
	pid_t	pid;
	int		fds[2];
	int		temp_fd;
	int		redir_to_pipe;

	(*token) += (getfd != 0);
	temp_fd = exec->stdout_fd;
	exec->curr_cmd = (*token)->cmd_num;
	redir_to_pipe = detect_pipe(*token, getfd, (*token)->prior - 1);
	if (filedata_after_parenthesis(exec, *token) == 1)
		return (redir_output(exec, token, redir_to_pipe, fds), 0);
	prep_recursion(exec, fds, temp_fd, getfd || redir_to_pipe);
	pid = fork();
	if (pid < 0)
		return (close(fds[0]), close(fds[1]), error(E_FORK, exec));
	else if (pid == 0)
		execute_loop(*token, exec);
	if (getfd == 0)
		exec->pid_list[(*token)->cmd_num] = pid;
	if (exec->stdout_fd != temp_fd)
		close_and_reset(&exec->stdout_fd);
	exec->stdout_fd = temp_fd;
	redir_output(exec, token, redir_to_pipe, fds);
	(*token) += ((*token)->prior == exec->prior_layer && getfd == 0);
	return (fds[0]);
}

static int	filedata_after_parenthesis(t_exec *exec, t_token *token)
{
	exec->file_not_found = 0;
	if (token->id != 0 && (token - 1)->type == RED_SUBSHELL)
		return (0);
	while (token->prior > exec->prior_layer)
		++token;
	if (is_red_sign(token->type) == _NO || token->prior > exec->prior_layer)
		return (0);
	if (get_file_data(exec, token, _NO) == 1)
	{
		exec->file_not_found = 1;
		return (1);
	}
	if (exec->last_out != -1)
		exec->stdout_fd = dup(STDOUT_FILENO);
	return (0);
}

static int	prep_recursion(t_exec *exec, int fds[2], int std_out, int do_pipe)
{
	fds[0] = 0;
	fds[1] = 0;
	if (do_pipe && pipe(fds) == 0)
	{
		if (exec->last_out == -1)
		{
			exec->stdout_fd = fds[1];
			dup2(fds[1], 1);
		}
		else
			close_and_reset(&exec->pipe_fds[1]);
	}
	save_temp_fds(exec, std_out, fds[0], do_pipe);
	return (0);
}

static int	redir_output(t_exec *exec, t_token **token, bool _pipe, int fds[2])
{
	bool	process_sub;

	if (exec->file_not_found && _pipe)
		pipe(fds);
	else if (!exec->file_not_found)
		remove_temp_fds(exec);
	dup2(exec->stdout_fd, 1);
	close(fds[1]);
	if (_pipe == 1)
	{
		close_and_reset(&exec->pipe_fds[0]);
		exec->pipe_fds[0] = fds[0];
	}
	if ((*token)->id != 0 && (*token - 1)->type == RED_SUBSHELL)
		process_sub = 1;
	else
		process_sub = 0;
	token_out_parenthesis(exec, token, process_sub);
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
