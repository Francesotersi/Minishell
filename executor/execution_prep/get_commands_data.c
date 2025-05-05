/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:32:36 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/29 11:51:59 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static void	get_one(t_exec *exec, t_token *token, int cmd_num, int cmd_layer);
static int	count_arguments(t_token *token, int cmd_layer);
static void	get_builtin_functions(t_exec *exec);
static void	add_placeholder(t_exec *exec, int cmd_num, int *i);

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
	int	cmd_layer;

	get_builtin_functions(exec);
	cmd_num = 0;
	while (token->content)
	{
		if (token->type == COMMAND)
		{
			cmd_layer = token->prior;
			get_one(exec, token, cmd_num, cmd_layer);
			exec->which_cmd[cmd_num] = \
			is_a_builtin_cmd(exec->commands[cmd_num][0]);
			++cmd_num;
			while ((++token)->type != COMMAND);
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
static void	get_one(t_exec *exec, t_token *token, int cmd_num, int cmd_layer)
{
	int	cmd_argc;
	int	i;

	tok_next(&token, COMMAND, cmd_layer, _YES);
	cmd_argc = count_arguments(token, cmd_layer);
	exec->commands[cmd_num] = (char **)ft_calloc(cmd_argc + 1, sizeof(char *));
	if (!exec->commands[cmd_num])
		error(E_MALLOC, exec);
	i = 0;
	while ((i != cmd_argc))
	{
		if (token->type == RED_SUBSHELL)
		{
			skip_deeper_layers(&token, cmd_layer);
			add_placeholder(exec, cmd_num, &i);
		}
		if ((token->content) && \
			(token->type == COMMAND || token->type == ARGUMENT))
		{
			exec->commands[cmd_num][i] = ft_strdup(token->content);
			if (!exec->commands[cmd_num][i++])
				error(E_MALLOC, exec);
		}
		token += (token->content != NULL);
	}
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
static int	count_arguments(t_token *token, int cmd_layer)
{
	int	counter;

	counter = 1;
	++token;
	while ("LOOP: counts every argument, considering parenthesis")
	{
		if (token->type == RED_SUBSHELL)
		{
			counter++;
			skip_deeper_layers(&token, cmd_layer);
		}
		if (is_exec_sep(token->type) == _YES || !token->content)
			break ;
		else if (token->id != 0 && cmd_layer != token->prior)
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

static void	add_placeholder(t_exec *exec, int cmd_num, int *i)
{
	exec->commands[cmd_num][*i] = ft_strdup("");
	if (!exec->commands[cmd_num][*i])
		error(E_MALLOC, exec);
	(*i)++;
}
