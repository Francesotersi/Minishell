/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:46:24 by alerusso          #+#    #+#             */
/*   Updated: 2025/02/18 13:21:22 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_manage_fds
{
	int		max_files;
	int		file_num;
	int		curr_fd;
	int		fd_index;
	char	*curr_file;
	int		fds[20];
	char	*filenames[20];
}			t_manage_fds;

#endif