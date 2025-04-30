/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:25:07 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/28 19:22:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

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

int	_reverse_strncmp(char *s1, char *s2, int len)
{
	int	i;
	int	j;
	int	diff;

	i = 0;
	j = 0;
	diff = 0;
	while (s1[i])
		++i;
	while (s2[j])
		++j;
	while (!diff && len && i != 0 && j != 0)
	{
		diff = s1[i--] != s2[j--];
		len--;
	}
	return (len + diff);
}

/*REVIEW - double_cmp
	A strncmp with double comparison.
	It is possible to set a number of chars to ignore for second string.
*/
int	double_cmp(char *s1, char *s2, int s1_len, int ignore_n_char)
{
	if (ft_strncmp(s1, s2, ft_strlen(s2) - ignore_n_char))
		return (1);
	if (ft_strncmp(s1, s2, s1_len))
		return (1);
	return (0);
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

void	write_here_doc(char *line, t_exec *exec, int fd)
{
	int		i;
	int		end;
	char	*env_str;
	char	temp;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			end = i + 1;
			while (line[end] && line[end] != ' ' && line[end] != '$')
				++end;
			temp = line[end];
			line[end] = 0;
			env_str = ft_getenv(*exec->env, line + i + 1, NULL);
			if (env_str)
				ft_putstr_fd(env_str, fd);
			if (!temp)
				break ;
			line[end] = temp;
			i = end - 1;
		}
		else
			write(fd, &line[i], 1);
	}
}

/*REVIEW - set_exit_status

//	Set exit status. Returns it.
*/
int	set_exit_status(t_exec *exec, int exit_status)
{
	*exec->exit_status = exit_status;
	return (exit_status);
}
