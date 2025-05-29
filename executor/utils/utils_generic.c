/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_generic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:04:20 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/29 12:43:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	bigger(int n1, int n2)
{
	return (n1 * (n1 >= n2) + n2 * (n1 < n2));
}

/*REVIEW - set_exit_code

//	Set exit status. Returns it.
*/
int	set_exit_code(t_exec *exec, int exit_code)
{
	*exec->exit_code = exit_code;
	exec->pid_list[exec->curr_cmd] = exit_code * -1;
	return (exit_code);
}

/*
//REVIEW - is_a_valid_executable

	This function is launched before command execution.
	It checks the executability of the program, and prints a bash_message if:

	1)	The executable is a directory 	(Exit status 126);
	2)	There executable does not exist (Exit status 127).
*/
int	is_a_valid_executable(t_exec *exec, int i)
{
	DIR	*dir;

	if (!exec->commands[i][0])
		return (_NO);
	dir = opendir(exec->commands[i][0]);
	if ((!dir) && (exec->which_cmd[i] || !access(exec->commands[i][0], X_OK)))
		return (_YES);
	if (exec->path && !dir)
		_cut_string(exec->commands[i][0], 0, 0);
	if (dir || access(exec->commands[i][0], F_OK) == 0)
	{
		if (dir)
		{
			bash_message(E_IS_DIRECTORY, exec->commands[i][0]);
			closedir(dir);
		}
		else
			bash_message(E_PERMISSION_DENIED, exec->commands[i][0]);
		return (set_exit_code(exec, 126), _NO);
	}
	if (exec->commands[i][0][0] == '/')
		bash_message(E_CMD_NOTFOUND, exec->commands[i][0]);
	else
		bash_message(E_NOFILE, exec->commands[i][0]);
	return (set_exit_code(exec, 127), _NO);
}

static long long int	ft_pow(long long int n, int p)
{
	int	num;

	num = n;
	p -= p == 19;
	if (n == 0 || p <= 0)
		return (1);
	while (p-- > 1)
		n *= num;
	return (n);
}

/*
//REVIEW - overflow_check

	Checks if the number in the string overflows the given limits.
	Returns 1 if it overflows, 0 if it does not.

//	1)	We check if the string is empty;
	2)	i is set to 1 if str[0] is '-' or '+';
	3)	We increase limit_size until the limit is less than 10;
	4)	We skip the leading zeros;
	5)	num_size is set to the number of digits in the string.
		Sign, leading zeroes are skipped;
	6)	We scroll the string until the current char is a digit;
	7)	If the current char is not a digit, there is an illegal
		char: therefore we return 1.
		If num_size is different from limit_size:
		if it's greater, there's an overflow. We return 1;
		If it's smaller, we return 0;
	8)	If num_size is equal to limit_size, we check every digit
		of the string and every digit of the limit: we stop
		when a different value is found;
	9)	If the current char is greater than the current limit
		digit, we return 1. Else, 0 is returned.
*/
int	overflow_check(char *s, long long max, long long min, int limit_size)
{
	long long int	limit;
	int				i;
	int				num_size;

	if (!s || !s[0])
		return (_YES);
	limit = max * (s[0] != '-') + min * (s[0] == '-');
	i = ((s[0] == '-') || (s[0] == '+'));
	max = limit;
	while (++limit_size && (limit > 9 || limit < -9))
		limit /= 10;
	limit = max;
	while (s[i] == '0')
		++i;
	num_size = ft_strlen(s + i);
	while (ft_isdigit(s[i]))
		++i;
	if (s[i] || num_size != limit_size)
		return (s[i] || num_size > limit_size);
	i -= num_size + 1;
	while (++i && --num_size && s[i] == limit / ft_pow(10, num_size) % 10 * \
		(-1 * (s[0] == '-') + 1 * (s[0] != '-')) + '0')
		;
	return (s[i] > limit / ft_pow(10, num_size) % 10 * \
		(-1 * (s[0] == '-') + 1 * (s[0] != '-')) + '0');
}
