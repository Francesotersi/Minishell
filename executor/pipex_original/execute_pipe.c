/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:34:46 by alerusso          #+#    #+#             */
/*   Updated: 2025/03/25 11:54:29 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	execute_fork(t_pipex *pipex, int *pipe_fds, int i, int prev);
int			change_files(t_pipex *pipex, int *pipe_fds, int i, int prev);
static void	close_all(t_pipex *pipex, int *pipe_fds, int prev);
static int	wait_all(t_pipex *pipex);

/*
	pipe_fds[0] = READ part of pipe temp file;
	pipe_fds[1] = WRITE part of pipe temp file.

	We want, for the first execution, to take infile, then
	we'll want the previously read head of the pipe.
	Non ci hai capito niente, eh?

	FIRST PIPE: pipe_fds[0] = READ
				pipe_fds[1] = WRITE

	We ignore the first read, because we start from infile!
	We'll print the first output in the first pipe temp file, with pipe_fds[1].

	Int the next command, we will need pipe_fds[0]: but not of the new pipe,
	but of the previous pipe!

	1)	Make the pipe;
	2)	Make the fork stuff;
	3)	Wait for all processes to finish.
*/
int	execute_pipe(t_pipex *pipex, t_settings *settings)
{
	int				err;
	int				i;
	static int		pipe_fds[2];
	int				prev;

	(void)settings;
	i = 0;
	prev = 0;
	while (pipex->commands[i])
	{
		if (pipe(pipe_fds) == -1)
			return (error(ER_PIPE_FAILED));
		err = execute_fork(pipex, pipe_fds, i, prev);
		if (err != 0)
			return (err);
		if (prev != 0)
			close(prev);
		prev = pipe_fds[0];
		close(pipe_fds[1]);
		++i;
	}
	err = wait_all(pipex);
	if (err != 0)
		return (err);
	return (close(pipe_fds[0]), 0);
}

/*
	If pid is -1, we have failed, then we'll abort anything;

	If pid is 0 (child), set the right files for STDIN and STDOUT, execute.
	If execve fails, the program continues and print an error (freeing memory).

	Else, save the pid on the pid list, that will be waited.
*/
static int	execute_fork(t_pipex *pipex, int *pipe_fds, int i, int prev)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (error(ER_FORK_FAILED));
	else if (pid == 0)
	{
		if (change_files(pipex, pipe_fds, i, prev) != 0)
			return (error(ER_DUP_FAILED));
		execve(pipex->options[i][0], pipex->options[i], pipex->options[i]);
		return (reset_memory(), exit(1), error(ER_EXECVE_FAILED));
	}
	pipex->pid_list[i] = pid;
	return (0);
}

/*	CONDITION		|||	COMMAND_ORDER	|||	INFILE		|||	OUTFILE	

	i == 0 ---------->	First cmd			infile			pipe[1]

	cmd[i + 1] != NULL	Not last cmd		prev. pipe[0]	pipe[1]

	cmd[i + 1] == NULL	Last cmd			prev. pipe[0]	outfile

----------------------------------------------------------------------
	EXAMPLE:

	INFILE	------->	pipex->fds[0] = 3;
	OUTFILE	------->	pipex->fds[1] = 4;
	
	FILE TEMP 1	--->  	pipe[0] = 5;		pipe[1] = 6;
	FILE TEMP 2	--->  	pipe[0] = 7;		pipe[1] = 8;	
	FILE TEMP 3	--->  	pipe[0] = 9;		pipe[1] = 10;

	For three commands:

	CMD_1	--------->	READ: 3(infile);		WRITE: 6(temp1, pipe[1]);
	CMD_2	--------->	READ: 5(temp1, pipe[0]);WRITE: 8(temp2, pipe[1]);
	CMD_3	--------->	READ: 7(temp1, pipe[0]);WRITE: 4(outfile);
	
----------------------------------------------------------------------
We open the pipes to store temp data.
Notice that last call to pipe could be avoided.
IMPROVE THIS BEFORE CORRECTION.
*/
int	change_files(t_pipex *pipex, int *pipe_fds, int i, int prev)
{
	int	err;

	err = 0;
	if ((i == 0) && (pipex->cmd_num != 0))
	{
		if (set_input_file(pipex->fds[0]) != 0)
			err = ER_DUP_FAILED;
		if (set_output_file(pipe_fds[1]) != 0)
			err = ER_DUP_FAILED;
	}
	else if ((pipex->commands[i + 1] != NULL) && (pipex->cmd_num != 0))
	{
		if (set_input_file(prev) != 0)
			err = ER_DUP_FAILED;
		if (set_output_file(pipe_fds[1]) != 0)
			err = ER_DUP_FAILED;
	}
	else
	{
		if (set_input_file(prev) != 0)
			err = ER_DUP_FAILED;
		if (set_output_file(pipex->fds[1]) != 0)
			err = ER_DUP_FAILED;
	}
	return (close_all(pipex, pipe_fds, prev), err);
}

/*
	Close everything.
	If prev (previous pipe_fds[0]) is not 0, close it too.
*/
static void	close_all(t_pipex *pipex, int *pipe_fds, int prev)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	close(pipex->fds[0]);
	close(pipex->fds[1]);
	if (prev != 0)
		close(prev);
}

/*
static void	close_one(int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}*/
/*
	Calls waitpid for every pid in the pid_list.
	Very cool, right?
*/
static int	wait_all(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->pid_list[i])
	{
		if (waitpid(pipex->pid_list[i], NULL, 0) == -1)
			return (ER_WAIT_FAILED);
		++i;
	}
	return (0);
}
