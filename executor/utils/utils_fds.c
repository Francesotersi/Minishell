/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:15:15 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/22 09:43:47 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*REVIEW - close_all

	Close all fds used by the executor part.
	Called before calling execve in the child.
*/
void	close_all(t_exec *exec)
{
	int				i;

	close_and_reset(&exec->pipe_fds[0]);
	close_and_reset(&exec->pipe_fds[1]);
	close_and_reset(&exec->stdin_fd);
	close_and_reset(&exec->stdout_fd);
	i = 0;
	while (exec->proc_sub_temp_fds[i])
		close_and_reset(&exec->proc_sub_temp_fds[i++]);
	i = 0;
	while (i != exec->last_cmd)
		close_and_reset(&exec->here_doc_fds[i++]);
}

/*REVIEW - save_process_substitution_fd

	Save the fd used by the process substitution.
	The proc_sub_fds array is scrolled until the first empty slot is found.
*/
void	save_process_substitution_fd(t_exec *exec, int proc_sub_fd)
{
	int	i;

	i = 0;
	while (exec->proc_sub_fds[i])
		++i;
	exec->proc_sub_fds[i] = proc_sub_fd;
}

/*REVIEW - close_temp_files

	Close the fd used in the current command for the here-doc,
	and all fds used for process substitution.
	Called when the command is finished, in execute_loop, after
	invoke_program function, in the parent.
*/
void	close_temp_files(t_exec *exec)
{
	int	i;

	close_and_reset(&exec->here_doc_fds[exec->curr_cmd]);
	i = 0;
	while (exec->proc_sub_fds[i])
	{
		close_and_reset(&exec->proc_sub_fds[i]);
		++i;
	}
}

/*REVIEW - close_and_reset

//		1)	Close an fd;
		2)	Sets it to zero.
*/
void	close_and_reset(int *fd)
{
	if (*fd >= 3)
		close(*fd);
	*fd = 0;
}

/*REVIEW - dup_and_reset

//		1)	Duplicate an fd;
		2)	Close it and sets it to zero.
*/
void	dup_and_reset(int *new_fd, int old_fd)
{
	dup2(*new_fd, old_fd);
	close_and_reset(new_fd);
}
