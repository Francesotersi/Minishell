/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:52:40 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/28 09:24:44 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	prep_recursion(t_exec *exec, int fds[2], int std_out, int do_pipe);
static int	redir_output(t_exec *exec, t_token **token, bool _pipe, int fds[2]);
static int	filedata_after_parenthesis(t_exec *exec, t_token *token);

/*
//REVIEW - manage_parenthesis

//	1)	We save the current command number;
	2)	We check if we have a redirection after the parenthesis,
		like: (ls) > file or (ls) < file;
	3)	If we fail to get the file data, we return;
	4)	We prepare the recursion, saving the current STDOUT and
		making a pipe to redirect the output. We make the pipe when:
		- we have a redirection, 	(ls) > file -->already done in 2);
		- we have a pipe, 			(ls) | cat;
		- we have a redir_subshell,	cat <(ls);
		pipe[0] and STDOUT are saved in proc_sub_temp_fds array;
	5)	We fork the process;
	6)	If we are in the child process, we execute the command.
		execute_loop takes care of ending the process;
	7)	If we are in the parent process, and we are not in a
		red_subshell, we save the PID of the child process,
		because red_subshell processes must not be waited by parent.
	8)	If the stdout_fd is changed, it means we have done a
		pipe. We close it, and reset the stdout_fd;
	9)	We redirect the output from the pipe, if we have one;
	10)	We move the token if there is a &&, ||, or |.
*/
int	manage_parenthesis(t_exec *exec, t_token **token, int getfd)
{
	pid_t	pid;
	int		fds[2];
	int		temp_fd;
	int		redir_to_pipe;

	(*token) += (getfd != 0);
	temp_fd = exec->stdout_fd;
	exec->curr_cmd = (*token)->cmd_num;
	redir_to_pipe = detect_pipe(*token, getfd, exec->prior_layer);
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

/*
//REVIEW - filedata_after_parenthesis

//	1)	If the previous token is a redirect_subshell, we return;
	2)	We go out of the parenthesis;
	3)	If the token is not a redirection, we return;
	4)	We get the file data. In case of error, we set the
		file_not_found flag to 1;
	5)	If there are output redirections (last_out != -1),
		we save the outfile file descriptor in the stdout_fd.
		the child will think it is the STDOUT.
*/
static int	filedata_after_parenthesis(t_exec *exec, t_token *token)
{
	exec->file_not_found = 0;
	exec->last_in = -1;
	exec->last_out = -1;
	if (token->id != 0 && (token - 1)->type == RED_SUBSHELL)
		return (0);
	while (token->prior > exec->prior_layer)
		++token;
	if (is_red_sign(token->type) == _NO)
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

/*
//REVIEW - prep_recursion

//	1)	If we need to send the output to a pipe, like (ls) | cat,
		we create it;
	2)	If there is a pipe, there are two cases:
		- we have only a pipe, 		(ls) | cat
		- we have a redirection, 	(ls) > file | cat
		In case there's a pipe only (last_out == -1),
		we dup the pipe output to the STDOUT, and
		save it in the stdout_fd.
		the child will think it is the STDOUT.
		In case of a redirection, we close the pipe output:
		in this way, cat will read from a empty file (real output
		goes to the file);
	3)	Temp fds are saved in proc_sub_temp_fds array.
*/
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
	exec->prior_layer += 1;
	return (0);
}

/*
//REVIEW - redir_output

//	1)	If the file_not_found flag is set and we need a pipe,
		we create it: otherwise cat would append.
		In every other case, we remote the temp fds;
	2)	We dup the stdout_fd to the STDOUT, and close the
		pipe output;
	3)	We redirect the output to the pipe, if we have one;
	4)	We exit from parenthesis.
		token_out_parenthesis behaves differently if it is a
		red_subshell:
		- normal:	(ls) > file <<DOC | cat	------>	We move to pipe |
		- subshell:	cat <(ls) > file	----------> We move to > file
*/
static int	redir_output(t_exec *exec, t_token **token, bool _pipe, int fds[2])
{
	bool	process_sub;

	if (exec->file_not_found && _pipe)
		pipe(fds);
	else if (!exec->file_not_found)
		remove_temp_fds(exec);
	dup2(exec->stdout_fd, 1);
	close_and_reset(&fds[1]);
	if (_pipe == 1)
	{
		close_and_reset(&exec->pipe_fds[0]);
		exec->pipe_fds[0] = fds[0];
	}
	if (exec->pipe_fds[0])
	{
		dup_and_reset(&exec->pipe_fds[0], 0);
	}
	if ((*token)->id != 0 && (*token - 1)->type == RED_SUBSHELL)
		process_sub = 1;
	else
		process_sub = 0;
	token_out_parenthesis(exec, token, process_sub);
	return (fds[0]);
}

/*
//REVIEW - get_subshell_filename

//	1)	We get the command argument index where the string must
		be inserted.
		Example: 				cat <(ls -a) infile <(ls -R)
		command argv start as:	{/bin/cat, "", infile, ""}
		then becomes:			{/bin/cat, "/dev/fd/5", infile, "/dev/fd/7"}
		Then, /dev/fd/5 argv index is 1, and /dev/fd/7 is 3;
	2)	We get from manage_parenthesis a input file descriptor
		from a subshell;
	3)	We convert it to a string, like /dev/fd/5.
		Normally, they are in odd positions (5, 7, 9...):
		This is because they are created in a pipe, and
		6, 8, 10 are used for the pipe output;
	4)	If process substitution is put before the command,
		like <(ls) cat, we return an error, like bash;
	5)	We set the filename in the command array;
	6)	We save the process substitution fd.
*/
int	get_subshell_filename(t_exec *exec, t_token **token, int cmd_num)
{
	int		filedata[2];
	int		pipe_fd;
	int		argv_index;
	char	*filename;
	char	*temp;

	argv_index = find_command_argument_index(exec, *token);
	if (argv_index <= 0)
		return (skip_deeper_layers(token, (*token)->prior), 1);
	filedata[0] = exec->last_in;
	filedata[1] = exec->last_out;
	pipe_fd = manage_parenthesis(exec, token, _YES);
	if (pipe_fd <= 0)
		error(E_OPEN, exec);
	temp = ft_itoa(pipe_fd);
	if (!temp)
		return (close(pipe_fd), error(E_MALLOC, exec));
	filename = ft_strjoin("/dev/fd/", temp);
	if (!filename)
		return (close(pipe_fd), free(temp), error(E_MALLOC, exec));
	free(exec->commands[cmd_num][argv_index]);
	exec->commands[cmd_num][argv_index] = filename;
	exec->last_in = filedata[0];
	exec->last_out = filedata[1];
	return (save_process_substitution_fd(exec, pipe_fd), free(temp), 0);
}
