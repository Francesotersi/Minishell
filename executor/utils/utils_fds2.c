/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fds2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:23:50 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/12 16:22:28 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:15:15 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/07 15:20:54 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

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

void	remove_temp_fds(t_exec *exec)
{
	int	i;

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
