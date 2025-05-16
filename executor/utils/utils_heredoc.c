/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:41:56 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/15 12:20:19 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
//REVIEW - write_here_doc

		This function takes as parameter a line of input from here_doc and
		its file descriptor.
		It writes the line on the here_doc fd, expanding environment variables.

//		1)	Iterate through the line until the end;
		2)	If a $ is found, find the end of the variable name;
		3)	Save the current character and replace it with a null terminator;
		4)	Replace the variable name with its value from the environment.
			If not found, do nothing;
		5)	Restore the character;
		6)	Write the line to the file descriptor.

*/
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
			while (!ft_strchr(" $\n", line[end]))
				++end;
			temp = line[end];
			line[end] = 0;
			env_str = get_env(*exec->env, line + i + 1);
			if (env_str)
				ft_putstr_fd(env_str, fd);
			line[end] = temp;
			i = end - 1;
		}
		else
			write(fd, &line[i], 1);
	}
}
