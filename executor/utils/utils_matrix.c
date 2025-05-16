/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:32:40 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/15 12:26:54 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*REVIEW - _free_matrix

//	Safely free a 2D matrix, even if NULL.
	Always return NULL.
*/
void	*_free_matrix(char **matrix)
{
	int	index;

	index = 0;
	if (!matrix)
		return (NULL);
	while (matrix[index])
	{
		if (matrix[index])
			free(matrix[index]);
		matrix[index] = NULL;
		++index;
	}
	if (matrix)
		free(matrix);
	return (NULL);
}

/*REVIEW - _free_three_d_matrix

//	Safely free a 3D matrix, even if NULL.
	Always return NULL.
*/
void	*_free_three_d_matrix(char ***matrix)
{
	int	index_one;
	int	index_two;

	index_one = 0;
	if (!matrix)
		return (NULL);
	while (matrix[index_one])
	{
		index_two = 0;
		while (matrix[index_one][index_two])
		{
			free(matrix[index_one][index_two]);
			matrix[index_one][index_two] = NULL;
			++index_two;
		}
		free(matrix[index_one]);
		matrix[index_one] = NULL;
		++index_one;
	}
	free(matrix);
	return (NULL);
}

/*
//REVIEW - _reverse_split

		Join a matrix of strings into a single string, 
		separated by a given character.
		The opposite of ft_split.

//		1) Count the total size of the strings in the matrix.
		2) Allocate memory for the resulting string.
		3) Copy each string from the matrix into the resulting string, 
		   separated by the given character.
		4) Initialize a variable to keep track of the current index 
			in the resulting string.
		5) Iterate through each string in the matrix.
		6) For each string, copy it into the resulting string at 
		   the current index.
		7) If it's not the first string, add the separator before copying.

*/
char	*_reverse_split(char **matrix, char separator)
{
	char	*string;
	int		i;
	int		size;
	int		j;

	i = -1;
	size = 0;
	while (matrix[++i])
	{
		size += ft_strlen(matrix[i]) + 1;
	}
	string = (char *)ft_calloc(size + 1, sizeof(char));
	if (!string)
		return (NULL);
	i = -1;
	j = 0;
	while (matrix[++i])
	{
		while (string[j])
			++j;
		if (j != 0 && separator)
			string[j++] = separator;
		_sub_strcpy(&string[j], matrix[i], "", EXCL);
	}
	return (string);
}

/*
//REVIEW - sort_matrix

	A bubble sort algorithm to sort a matrix of strings in 
	ASCII ascending order.
*/
void	sort_matrix(char **matrix)
{
	char	*temp;
	int		i;
	int		j;

	if (!matrix || !matrix[0])
		return ;
	i = 0;
	while (matrix[i + 1])
	{
		j = 0;
		while (matrix[j + 1])
		{
			if (ft_strncmp(matrix[j], matrix[j + 1], INT_MAX) > 0)
			{
				temp = matrix[j];
				matrix[j] = matrix[j + 1];
				matrix[j + 1] = temp;
			}
			++j;
		}
		++i;
	}
}

/*
//REVIEW - lowest_ascii_matrix

	Takes as parameters a matrix of strings and a string (current).
	Returns the string with the lowest ASCII value in the matrix,
	that is bigger than the current string.
	Returns NULL if the matrix is empty or if no valid string is found.
	Used to sort the output of export without arguments.
*/
char	*lowest_ascii_matrix(char **matrix, char *current)
{
	char	*lowest;
	int		i;

	if (!matrix || !matrix[0])
		return (NULL);
	lowest = NULL;
	i = 0;
	while (matrix[i])
	{
		if ((current && ft_strncmp(matrix[i], current, INT_MAX) <= 0))
		{
			++i;
			continue ;
		}
		if (!lowest || ft_strncmp(matrix[i], lowest, INT_MAX) < 0)
			lowest = matrix[i];
		++i;
	}
	return (lowest);
}
