/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:39:35 by alerusso          #+#    #+#             */
/*   Updated: 2025/03/25 11:54:53 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
	1)	Open files;
	2)	We try to put stuff with dup2 on fd 0 and 1.
		Just to test if there are errors;
	3)	If there aren't we save in our fds array:
		-fd 0;
		-fd 1;
		-fd infile;
		-fd outfile.
		fd 0 is saved as INT_MAX as placeholder.
		Everyone will be closed in reset_memory(). 
*/
int	dup_fds(t_pipex *pipex, t_settings *settings)
{
	int	fd_infile;
	int	fd_outfile;

	(void)settings;
	fd_infile = open(pipex->infile, INFILE, 0666);
	if (fd_infile < 0)
		return (ER_OPEN_FAILED);
	pipex->fds[0] = fd_infile;
	fd_outfile = open(pipex->outfile, OUTFILE, 0666);
	if (fd_outfile < 0)
		return (ER_OPEN_FAILED);
	pipex->fds[1] = fd_outfile;
	if (dup2(fd_infile, 0) == -1)
		return (ER_DUP_FAILED);
	pipex->fds[2] = 1;
	if (dup2(fd_outfile, 1) == -1)
		return (ER_DUP_FAILED);
	pipex->fds[3] = INT_MAX;
	return (0);
}

int	set_output_file(int outfile_fd)
{
	if (dup2(outfile_fd, 1) == -1)
		return (ER_DUP_FAILED);
	return (0);
}

int	set_input_file(int infile_fd)
{
	if (dup2(infile_fd, 0) == -1)
		return (ER_DUP_FAILED);
	return (0);
}
