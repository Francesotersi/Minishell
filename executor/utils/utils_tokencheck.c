/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokencheck.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:10:30 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/15 13:41:26 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*REVIEW - 
	is_redirector_sign searches for:	
										{>}
										{<}
										{>>}
										{<<}
*/
int	is_red_sign(int sign)
{
	if (sign == RED_OUT)
		return (_YES);
	else if (sign == RED_IN)
		return (_YES);
	else if (sign == RED_O_APPEND)
		return (_YES);
	else if (sign == HERE_DOC)
		return (_YES);
	else if (sign == RED_SUBSHELL)
		return (_YES);
	return (_NO);
}

/*REVIEW - 
	is_redirector_input_sign searches for:	
										{<}
										{<<}
	
	Returns 1 (_YES) on success;
	Returns 0 (_NO) on failure.
*/
int	is_red_input_sign(int sign)
{
	if (sign == RED_IN)
		return (_YES);
	else if (sign == HERE_DOC)
		return (_YES);
	return (_NO);
}

/*REVIEW - 
	is_redirector_output_sign searches for:	
										{>}
										{>>}
	
	Returns 1 (_YES) on success;
	Returns 0 (_NO) on failure.
*/
int	is_red_output_sign(int sign)
{
	if (sign == RED_OUT)
		return (_YES);
	else if (sign == RED_O_APPEND)
		return (_YES);
	return (_NO);
}

/*REVIEW - 
	is_execution_separator searches for:	
											{|}
											{&&}
											{||}
	
	Returns 1 (_YES) on success;
	Returns 0 (_NO) on failure.
*/
int	is_exec_sep(int sign)
{
	if (sign == PIPE)
		return (_YES);
	else if (sign == AND)
		return (_YES);
	else if (sign == OR)
		return (_YES);
	return (_NO);
}

/*REVIEW - is_a_builtin_cmd

		Returns the builtin enum index, or zero if it is not a builtin.
*/
int	is_a_builtin_cmd(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", 4) && !ft_strncmp(cmd, "echo", len))
		return (B_ECHO);
	else if (!ft_strncmp(cmd, "cd", 2) && !ft_strncmp(cmd, "cd", len))
		return (B_CD);
	else if (!ft_strncmp(cmd, "pwd", 3) && !ft_strncmp(cmd, "pwd", len))
		return (B_PWD);
	else if (!ft_strncmp(cmd, "export", 6) && !ft_strncmp(cmd, "export", len))
		return (B_EXPORT);
	else if (!ft_strncmp(cmd, "unset", 5) && !ft_strncmp(cmd, "unset", len))
		return (B_UNSET);
	else if (!ft_strncmp(cmd, "env", 3) && !ft_strncmp(cmd, "env", len))
		return (B_ENV);
	else if (!ft_strncmp(cmd, "exit", 4) && !ft_strncmp(cmd, "exit", len))
		return (B_EXIT);
	return (_NO);
}
