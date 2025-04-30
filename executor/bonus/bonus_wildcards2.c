/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_wildcards2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:11:14 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/28 19:19:18 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	fill_matrix(t_wildcard *wdata, char **matrix);
static int	check_one(char *search, char *file);

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
	sort_matrix(matrix);
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
		if (file->d_name[0] != '.' && check_one(wdata->search, file->d_name))
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

static int	check_one(char *search, char *file)
{
	int	f_i;
	int	s_i;

	f_i = 0;
	s_i = 0;
	while (search[s_i])
	{
		if (!file[f_i])
			return (0);
		else if (search[s_i] != '*')
		{
			while (file[f_i] && file[f_i] != search[s_i])
			{
				if (s_i == 0 || search[s_i - 1] != '*')
					return (0);
				++f_i;
			}
			++f_i;
		}
		++s_i;
	}
	if (search[s_i - 1] != '*' && file[f_i])
		return (0);
	return (1);
}
