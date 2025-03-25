/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:25:11 by alerusso          #+#    #+#             */
/*   Updated: 2025/03/25 11:55:07 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	compare_input(char *line, char *limiter);

/*
	Just a split of every command.
	Super simple.

	If the command does not exits, we put an empty 
	matrix of options.
*/
int	get_options(t_pipex *pipex)
{
	int	index;

	index = 0;
	while (pipex->commands[index])
	{
		if (ft_strncmp(pipex->commands[index], "error!", 6) == 0)
		{
			pipex->cmd_num -= 1;
			pipex->options[index] = ft_split("err", '!');
			if (pipex->options[index] == NULL)
				return (ER_MALLOC);
			++index;
			continue ;
		}
		pipex->options[index] = ft_split(pipex->commands[index], ' ');
		if (pipex->options[index] == NULL)
			return (ER_MALLOC);
		++index;
	}
	return (0);
}

/*
	The outfile is always the last argument.
*/
int	get_second_filename(char *argv[], t_pipex *pipex)
{
	int	i;
	int	len;

	i = 0;
	while (argv[i] != NULL)
		++i;
	--i;
	len = ft_strlen(argv[i]) + 1;
	pipex->outfile = (char *)ft_calloc(len, sizeof(char));
	if (!pipex->outfile)
		return (ER_MALLOC);
	ft_strlcpy(pipex->outfile, argv[i], len);
	return (0);
}

/*
	here doc is a temp file that must be erase (with unlink) at the end
	of the execition.

	It needs a warning string ("here_doc") and a LIMITER.

	1)	We save the limiter len;
	2)	We try to open the here_doc file, with OUTFILE permissions because we
		need to write on it.
		Later in execution we'll open it with INFILE permissions;
	3)	We trigger the here_doc bool on, since we have succeded on opening it;
	4)	We print a message for the user;
	5)	We call get next line for every line the user asks us;
	6)	We close the file when the user print the LIMITER.
*/
int	get_here_doc_file(char *argv[], t_pipex *pipex)
{
	char	*line;
	int		fd;

	fd = open("here_doc", OUTFILE, 0666);
	if (fd < 0)
		return (ER_OPEN_FAILED);
	pipex->here_doc_bool = YES;
	pipex->infile = ft_strdup("here_doc");
	if (!pipex->infile)
		return (close(fd), ER_MALLOC);
	l_printf("\nInsert the input file contents, line per line.\n");
	l_printf("Press enter to submit. Insert the limiter to stop.\n\n");
	line = gnl(0);
	while ((line) && (compare_input(line, argv[2])) != 2)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = gnl(0);
	}
	if (!line)
		return (close(fd), ER_MALLOC);
	free(line);
	return (close(fd));
}

static int	compare_input(char *line, char *limiter)
{
	int			double_equality;
	static int	limiter_len = -1;

	double_equality = 0;
	if (limiter_len == -1)
		limiter_len = ft_strlen(limiter);
	if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
		double_equality += 1;
	if (ft_strncmp(line, limiter, limiter_len) == 0)
		double_equality += 1;
	return (double_equality);
}

int	get_commands_recursion(char *argv[], t_pipex *pipex, int i)
{
	if (i == pipex->cmd_num)
		return (0);
	else if (pipex->commands == NULL)
		return (ER_MALLOC);
	pipex->commands++;
	return (get_commands(argv, pipex, i));
}
