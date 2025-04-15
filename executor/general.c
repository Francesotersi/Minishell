/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:32:40 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/14 12:04:08 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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

/*REVIEW - count_commands

//	Count the number of command block in the commands line sent by parsing.
	exec allocation size depend on this number.
	Checks if there are pipe on the commands line.
*/
int	count_commands(t_exec *exec, t_token *tokens)
{
	int	cmd_num;
	int	pipe_num;

	cmd_num = 0;
	pipe_num = 0;
	while (tokens->content != NULL)
	{
		pipe_num += (tokens->type == PIPE);
		cmd_num += (tokens->type == COMMAND);
		++tokens;
	}
	exec->at_least_one_pipe = pipe_num > 0;
	return (cmd_num);
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
