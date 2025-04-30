/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:32:40 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/28 19:22:43 by alerusso         ###   ########.fr       */
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

/*REVIEW - _ft_strjoin_free

//	Like strjoin, but frees both string.
*/
char	*_ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;
	int		index;
	int		size;

	if ((!s1) || (!s2))
		return (free(s1), free(s2), NULL);
	index = 0;
	while (s1[index])
		++index;
	size = index;
	index = 0;
	while (s2[index])
		++index;
	size += index;
	new_str = (char *)ft_calloc(size + 2, sizeof(char));
	if (!new_str)
		return (free(s1), free(s2), NULL);
	index = -1;
	while (s1[++index])
		new_str[index] = s1[index];
	size = -1;
	while (s2[++size])
		new_str[index++] = s2[size];
	return (free(s1), free(s2), new_str);
}

int	bigger(int n1, int n2)
{
	return (n1 * (n1 >= n2) + n2 * (n1 < n2));
}
