/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_generic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:04:20 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/11 11:57:58 by alerusso         ###   ########.fr       */
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

	if (exec->which_cmd[i] != 0)
		return (_YES);
	if (!exec->commands[i][0])
		return (_NO);
	dir = opendir(exec->commands[i][0]);
	if (dir)
	{
		bash_message(E_IS_DIRECTORY, _cut_string(exec->commands[i][0], 0, 0));
		closedir(dir);
		set_exit_code(exec, 126);
		return (_NO);
	}
	else if (access(exec->commands[i][0], F_OK | X_OK) != 0)
	{
		bash_message(E_CMD_NOTFOUND, _cut_string(exec->commands[i][0], 0, 0));
		set_exit_code(exec, 127);
		return (_NO);
	}
	return (_YES);
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


int	overflow_check(char *s, long long max, long long min)
{
	long long int	limit;
	int				i;
	int				limit_size;
	int				num_size;

	if (!s || !s[0])
		return (_YES);
	limit = max * (s[0] != '-') + min * (s[0] == '-');
	i = (s[0] == '-') || (s[0] == '+');
	limit_size = 0;
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
		(-1 * (s[0] == '-') + 1 * (s[0] != '-')) + '0');
	return (s[i] > limit / ft_pow(10, num_size) % 10 * \
		(-1 * (s[0] == '-') + 1 * (s[0] != '-')) + '0');
}// exit -9223372036854775808
/*
	display s[i]
	display limit / ft_pow(10, num_size) % 10 * (-1 * (s[0] == '-') + 1 * (s[0] != '-')) + '0'
*/
