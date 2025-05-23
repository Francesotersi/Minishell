/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_wildcards2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:11:14 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/22 20:47:53 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	fill_matrix(t_wildcard *wdata, char **matrix);
static int	check_one(char *search, char *file);
static int	check_end(char *search, char *file, int s_i);

/*REVIEW - fill_occurrences

//		1)	A matrix of size dir_size is created;
		2)	The matrix is filled with the directory contents;
		3)	If there are no elements, 
			the new string is the dup of the search string (/bin/g*e*p);
		4)	We sort the matrix;
		5)	The matrix is transformed into a string. Elements are
			separated by a space.
*/
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

/*REVIEW - fill_matrix

//		We store every valid file in the matrix.
		Valid files are those that match the search string,
		and are not hidden files (starting with a dot).
*/
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

/*REVIEW - fill_matrix

//		The tricky one in wildcards.
		Cases:
		-> search = "*"		file = "test"	-> YES
		-> search = "t*"	file = "test"	-> YES
		-> search = "test*"	file = "test"	-> NO (there must be a char after)
		-> search = "*test"	file = "test"	-> NO (there must be a char before)
		-> search = "*test*"file = "test	-> NO (both)
		-> search = "t*s*"	file = "test"	-> YES
		-> search = "*****"	file = "test"	-> YES
		-> search = "tzt*"	file = "test"	-> NO (z is not in test)

		1)	We go through the search string.
			s_i = search index;
			f_i = file index;
		2)	If the search string is not finished, and the file is finished,
			the file is invalid;
		2)	If the search char is 'finished, 
			while the previous char is not '*' and file is not finished,
			the file is valid.
			These checks are done to "test*" and "*test" cases;
		3)	If the search char is '*', we skip it;
		4)	If the search char is not '*', we go through the file
			until we find the search char.
			If we find it, we go to the next.
			If the search is not found, and the file index is 0
			while the previous char is not '*', the file is invalid,
			because multiple chars (*) are not allowed.
*/
static int	check_one(char *search, char *file)
{
	int	f_i;
	int	s_i;

	f_i = 0;
	s_i = 0;
	while (search[s_i])
	{
		if (!file[f_i])
			return (_NO);
		else if (search[s_i] != '*')
		{
			while (file[f_i] != search[s_i])
			{
				if (!file[f_i] || s_i == 0 || search[s_i - 1] != '*')
					return (_NO);
				++f_i;
			}
			++f_i;
		}
		++s_i;
	}
	if (s_i != 0 && ((search[s_i - 1] == '*' && !file[f_i]) || \
		check_end(search, file + f_i, s_i) == 1))
		return (_NO);
	return (_YES);
}

static int	check_end(char *search, char *file, int s_i)
{
	if (!*file || search[s_i - 1] == '*')
		return (0);
	while (s_i > 0 && search[s_i - 1] != '*')
		--s_i;
	file = _ft_strrstr(file, search + s_i);
	if (!file)
		return (1);
	while (search[s_i])
	{
		++s_i;
		file++;
	}
	if (*(file + 1))
		return (1);
	return (0);
}
