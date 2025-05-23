/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fds2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:15:15 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/23 09:33:41 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*REVIEW - save_temp_fds

 	This function saves the temporary file descriptors for the current process.
	It used in manage_parenthesis, before invoke a subshell.
	It takes two file descriptors (fd1 and fd2)
 	and a flag (do_pipe) indicating if 
	in manage_parenthesis a pipe or a red_subshell is done.
	fd1 = REAL_STDOUT,	fd2 = pipe[0] used for subshell.
	These fds will be closed in every child that calls execve.
 	The function iterates through the proc_sub_temp_fds array to find 
 	the next available index, and then saves the file descriptors accordingly.
	Not always fds must be saved to be resetted: a placeholder (-1) is set
	in the array, in these cases.
	Cases are:
	-	PIPES [(ls) | cat]:				both REAL_STDOUT and pipe[0] are saved;
	-	SUBSHELL_REDIRECTION [<(ls)]:	both REAL_STDOUT and pipe[0] are saved;
	-	REDIRECTION [(ls) > file.txt]:	only REAL_STDOUT is saved;
	-	NO PIPE/REDIRECTION: [(ls)]		nothing is saved.

//	1)	We scroll through the proc_sub_temp_fds array to find 
		the first empty slot;
	2)	If do_pipe is true, we save fd1 and fd2 in the array;
	3)	If do_pipe is false, but the output was redirected on a file,
		(ls) > file.txt, we save fd1 in the array, and -1 in the next slot;
	4)	If do_pipe is false and the output was not redirected, we save -1 
		in the array twice.
 */
void	save_temp_fds(t_exec *exec, int fd1, int fd2, int do_pipe)
{
	int	i;

	i = 0;
	while (exec->proc_sub_temp_fds[i])
		++i;
	if (do_pipe)
	{
		exec->proc_sub_temp_fds[i++] = fd1;
		exec->proc_sub_temp_fds[i] = fd2;
	}
	else
	{
		if (exec->last_out != -1)
			exec->proc_sub_temp_fds[i++] = fd1;
		else
			exec->proc_sub_temp_fds[i++] = -1;
		exec->proc_sub_temp_fds[i] = -1;
	}
}

/*REVIEW - remove_temp_fds

	This function removes the temporary file descriptors saved in
	save_temp_fds.
	
//	1)	If there were issues in opening a file, the subshell has
		not been created, and no fds have been saved.
		Therefore, we return;
	2)	We scroll through the proc_sub_temp_fds array to find
		the first empty slot;
	3)	We go back one slot, and remove the last saved fd;
	4)	We do it again.
 */
void	remove_temp_fds(t_exec *exec)
{
	int	i;

	exec->prior_layer -= 1;
	if (exec->file_not_found)
		return ;
	i = 0;
	while (exec->proc_sub_temp_fds[i])
		++i;
	if (i && exec->file_not_found == 0)
		exec->proc_sub_temp_fds[--i] = 0;
	if (i && exec->file_not_found == 0)
		exec->proc_sub_temp_fds[--i] = 0;
}
