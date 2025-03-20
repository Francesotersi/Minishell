/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:08:08 by ftersill          #+#    #+#             */
/*   Updated: 2025/03/20 17:12:42 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "debug.h"
# include "debug_resources/all.h"

int	testing(int test_num);

int	main(int argc, char **argv)
{
	int		fd;
	int		n;
	char	*filename;
	int		i;
	char	*line;

	if (argv == NULL)
		return (fd_printf(2, "\nInsert a file num.\n"));
	filename = ft_strjoin("debug_resources/input_samples/", argv[1]);
	if (!filename)
		return (fd_printf(2, "\nMalloc failed\n"));
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
		return (fd_printf(2, "Failed to open file"));
	give_filedata(fd, filename);
	n = num_line(1, "[Caso");
	line = get_n_line(fd, n);
	i = 0;
	while (testing(i))
		++i;
	del_filedata();
}

int	testing(int test_num)
{
	char	***matrix;
	char	*test;
	
	test = ft_strjoin
}
