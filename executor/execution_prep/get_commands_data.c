/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:32:36 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/21 12:15:57 by ftersill         ###   ########.fr       */
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
*/
int	get_commands_data(t_exec *exec, t_token *token)
{
	int	cmd_num;
	int	cmd_layer;

	get_builtin_functions(exec);
	while (token->content)
	{
		if (token->type == COMMAND)
		{
			cmd_layer = token->prior;
			cmd_num = token->cmd_num;
			get_one(exec, token, cmd_num, cmd_layer);
			exec->which_cmd[cmd_num] = \
			is_a_builtin_cmd(exec->commands[cmd_num][0]);
			++token;
		}
		else
			++token;
	}
	cmd_num = -1;
	while (++cmd_num != exec->last_cmd)
		if (!exec->commands[cmd_num])
			create_empty_matrix(exec, cmd_num);
	return (0);
}

/*REVIEW - get_one

//	1)	We count the number of arguments (including the command itself);
	2)	We alloc a matrix for the command;
	3)	We iterate for all arguments, and we set them in the matrix;
	4)	If we find a RED_SUBSHELL token, we add a placeholder
		in the matrix (see add_placeholder);
	5)	If we find a COMMAND or ARGUMENT token, we set it in the matrix.
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
		while (token->type == RED_SUBSHELL && cmd_layer == token->prior)
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
	2)	If we find a RED_SUBSHELL token, we increase the counter (it will
		be a placeholder in the matrix, see add_placeholder);
	3)	If we find a COMMAND or ARGUMENT token, we increase the counter;
	4)	If there is a execution separator (&&, ||, |), or a difference in
		parenthesis layer, we break.
*/
static int	count_arguments(t_token *token, int cmd_layer)
{
	int	counter;

	counter = 1;
	++token;
	while ("LOOP: counts every argument, considering parenthesis")
	{
		while (token->type == RED_SUBSHELL && cmd_layer == token->prior)
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

/*REVIEW - add_placeholder

//	redirect_Subshell are not counted in the matrix, but they are
		needed to be there for the redirection to work.
		We add a placeholder in the matrix, so we can use it
		in the get_subshell_filename function.

	Example:
		/bin/cat <(ls -a) infile <(ls -R)
		argv[0] = /bin/cat
		argv[1] = ""
		argv[2] = infile
		argv[3] = ""
		argv[4] = NULL
*/
static void	add_placeholder(t_exec *exec, int cmd_num, int *i)
{
	exec->commands[cmd_num][*i] = ft_strdup("");
	if (!exec->commands[cmd_num][*i])
		error(E_MALLOC, exec);
	(*i)++;
}
