/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_wildcards2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:11:14 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/14 22:54:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	fill_matrix(t_wildcard *wdata, char **matrix);
static int	check_one(t_wildcard *wdata, char *file);

char	*fill_occurrences(t_wildcard *wdata)
{
	char	**matrix;
	char	*new_str;

	matrix = ft_calloc(wdata->dir_size + 1, sizeof(char *));
	if (!matrix)
		return (NULL);
	if (fill_matrix(wdata, matrix))
		return (_free_matrix(matrix), NULL);
	if (wdata->dir_size == 0)
		return (_free_matrix(matrix), ft_strdup(wdata->old_str));
	new_str = _reverse_split(matrix, ' ');
	if (!new_str)
		return (_free_matrix(matrix), NULL);
	return (_free_matrix(matrix), new_str);
}

static int	fill_matrix(t_wildcard *wdata, char **matrix)
{
	DIR				*dir;
	int				i;
	struct dirent	*file;

	dir = opendir(wdata->dir_path);
	if (!dir)
		return (E_OPEN);
	i = 0;
	file = readdir(dir);
	while (file)
	{
		if (check_one(wdata, file->d_name))
		{
			matrix[i] = ft_strdup(file->d_name);
			if (!matrix[i])
				return (closedir(dir), E_MALLOC);
			++i;
		}
		file = readdir(dir);
	}
	wdata->dir_size = i;
	closedir(dir);
	return (0);
}

static int	check_one(t_wildcard *wdata, char *file)
{
	
	if ((!wdata->start || !ft_strncmp(wdata->start, file, wdata->start_len))\
	 && (!wdata->end || !_reverse_strncmp(wdata->end, file, wdata->end_len)))
		return (_YES);
	else
		return (_NO);
}
