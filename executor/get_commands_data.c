/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:32:36 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/12 17:35:09 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	get_one(t_exec *exec, t_token **token, int cmd_num);
static int	count_arguments(t_token *token);
static void	get_builtin_functions(t_exec *exec);

/*REVIEW - get_commands_data

//	1)	Stores data in exec->builtins, an array of functions.
		See get_builtin_functions below;
	2)	Iterate for all commands line. When finding a command,
		increase the cmd_num index;
	3)	If a token is a COMMAND, we alloc and set a matrix (an argv)
		for it (see get_one);
	4)	We check if it is a builtin. If it is, we store the value of
		the builtin in the exec->which_cmd array, in position [cmd_num].
		If it is not a builtin, 0 (_NO) will be saved.
		See enum e_builtin for every builtin value;
	5)	If the token is not a COMMAND, we just go to next token.
		In add_one, we go to next token that is not a COMMAND or ARGUMENT.
*/
int	get_commands_data(t_exec *exec, t_token *token)
{
	int	cmd_num;

	get_builtin_functions(exec);
	cmd_num = 0;
	while (token->content)
	{
		if (token->type == COMMAND)
		{
			get_one(exec, &token, cmd_num);
			exec->which_cmd[cmd_num] = \
			is_a_builtin_cmd(exec->commands[cmd_num][0]);
			++cmd_num;
		}
		else
			++token;
	}
	return (0);
}

/*REVIEW - get_one

//	1)	Stores data in exec->builtins, an array of functions.
		See get_builtin_functions below;
	2)	Iterate for all commands line. When finding a command,
		increase the cmd_num index;
	3)	If a token is a COMMAND, we alloc and set a matrix (an argv)
		for it (see get_one);
	4)	We check if it is a builtin. If it is, we store the value of
		the builtin in the exec->which_cmd array, in position [cmd_num].
		If it is not a builtin, 0 (_NO) will be saved.
		See enum e_builtin for every builtin value;
	5)	If the token is not a COMMAND, we just go to next token.
		In add_one, we go to next token that is not a COMMAND or ARGUMENT.
*/
static int	get_one(t_exec *exec, t_token **token, int cmd_num)
{
	int	command_argc;
	int	i;

	command_argc = count_arguments(*token);
	exec->commands[cmd_num] = \
	(char **)ft_calloc(command_argc + 1, sizeof(char *));
	if (!exec->commands[cmd_num])
		error(E_MALLOC, exec);
	i = 0;
	while ((i != command_argc))
	{
		if ((*token)->type == COMMAND || (*token)->type == ARGUMENT)
		{
			exec->commands[cmd_num][i] = ft_strdup((*token)->content);
			if (!exec->commands[cmd_num][i])
				error(E_MALLOC, exec);
			++i;
		}
		++(*token);
	}
	return (0);
}

/*REVIEW - count_arguments

//	1)	Counter starts from 1, because elements starts from 0 (argv[0]);
	2)	We counts every argument, considering parenthesis;
	3)	If the token is a execution separator (|, &&, ||) or not exists,
		stop the counting;
	4)	If token priority is different than its previous,
		stop the counting;
	5)	If token is a COMMAND or ARGUMENT, increase counter.
*/
static int	count_arguments(t_token *token)
{
	int	counter;

	counter = 1;
	++token;
	while ("LOOP: counts every argument, considering parenthesis")
	{
		if (is_exec_sep(token->type) == _YES || !token->content)
			break ;
		else if (token->id != 0 && token->prior != (token - 1)->prior)
			break ;
		else if (token->type == COMMAND || token->type == ARGUMENT)
			counter++;
		++token;
	}
	return (counter);
}

/*REVIEW - get_builtin_functions

//	Self-explanatory.
*/
static void	get_builtin_functions(t_exec *exec)
{
	exec->builtins[B_ECHO] = ft_echo;
	exec->builtins[B_CD] = ft_cd;
	exec->builtins[B_PWD] = ft_pwd;
	exec->builtins[B_EXPORT] = ft_export;
	exec->builtins[B_UNSET] = ft_unset;
	exec->builtins[B_ENV] = ft_env;
	exec->builtins[B_EXIT] = ft_exit;
}
