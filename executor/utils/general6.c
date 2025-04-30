/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:15:15 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/28 19:23:00 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	close_all(t_exec *exec)
{
	t_debug_data	*debug;

	close_and_reset(&exec->pipe_fds[0]);
	close_and_reset(&exec->pipe_fds[1]);
	close_and_reset(&exec->stdin_fd);
	close_and_reset(&exec->stdout_fd);
	if (exec->debug)
	{
		debug = exec->main_struct_pointer;
		close_and_reset(&debug->fd_to_close);
	}
}

void	save_process_substitution_fd(t_exec *exec, int proc_sub_fd)
{
	int	i;

	i = 0;
	while (exec->proc_sub_fds[i])
		++i;
	exec->proc_sub_fds[i] = proc_sub_fd;
}

void	close_temp_files(t_exec *exec)
{
	int	i;

	close_and_reset(&exec->here_doc_fds[exec->cmd_num]);
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

void	dup_and_reset(int *new_fd, int old_fd)
{
	dup2(*new_fd, old_fd);
	close_and_reset(new_fd);
}