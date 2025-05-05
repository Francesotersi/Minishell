/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:25:07 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/01 12:49:57 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

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
