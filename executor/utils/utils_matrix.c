/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:32:40 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/04 11:21:39 by alerusso         ###   ########.fr       */
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

char	*_reverse_split(char **matrix, char separator)
{
	char	*string;
	int		i;
	int		size;
	int		j;

	i = 0;
	size = 0;
	while (matrix[i])
	{
		size += ft_strlen(matrix[i]) + 1;
		++i;
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
