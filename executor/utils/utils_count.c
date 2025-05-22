/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:24:35 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/22 10:55:27 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*REVIEW - count_commands

//	Returns the number of command block in the commands line sent by parsing.
	exec allocation size depend on this number.
*/
int	count_commands(t_token *token)
{
	while (token->content)
		++token;
	return (token->cmd_num);
}

/*REVIEW - find_command_argument_index

	This function takes as input a token, and returns the index of
	that token in the command argument argv.
	For example, if the command is "ls -l -a", and the token is "-l",
	the function will return 1, because "-l" is the first argument
	of the command "ls -l -a".
	This is useful for determining the position of a redir_subshell token
	in the command line, so that we can fill its placeholder.

	example:	ls -l <(ls) -a
	start as:	{/bin/ls, -l, "", -a, NULL}
	must become:{/bin/ls, -l, "/dev/fd/5", -a, NULL}
	So we must return the index for the redir_subshell token, which is 2.

//	1)	We start from the token and go back to the first command token
	2)	We count the number of command arguments until we reach the
		first command token.
	3)	If we find a redir_subshell token, we check if it is the first
		command argument. If it is, we return -1.
	4)	If we find a command token, we increment the command argument
		count.
	5)	If we find an argument token, we increment the command argument
		count.
	6)	If we reach the current token, we return the command argument
		count.
*/
int	find_command_argument_index(t_exec *exec, t_token *token)
{
	t_token	*current;
	int		cmd_argc;

	current = token;
	cmd_argc = 0;
	while (token->id != 0 && (token->prior >= (token - 1)->prior || \
			token->cmd_num != (token - 1)->cmd_num))
		--token;
	while (token != current)
	{
		if (token->type == COMMAND)
			cmd_argc = 1;
		else if (token->type == RED_SUBSHELL)
		{
			if (cmd_argc == 0)
				return (-1);
			skip_deeper_layers(&token, exec->prior_layer);
			--token;
			++cmd_argc;
		}
		else
			cmd_argc += token->type == ARGUMENT;
		++token;
	}
	return (cmd_argc);
}

/*REVIEW - proc_sub_num

	Returns the command block with the most redir_subshells.
	Used to allocate the right size for 
	the proc_sub_fds and proc_sub_temp_fds array.

//	1)	We start from the first token and go to the end of the command line;
	2)	We count the number of red_subshells in the current command block;
	3)	If we find a red_subshell token, we increment the red_subshell count;
	4)	If we find a command token, we increment the command argument
		count;
	5)	The biggest red_subshell count is returned in the record variable.
*/
int	proc_sub_num(t_token *token)
{
	int		record;
	int		curr_score;
	int		curr_layer;
	t_token	*curr_token;

	record = 0;
	while (token->content)
	{
		curr_token = token;
		curr_layer = token->prior;
		curr_score = 0;
		while (token->prior >= curr_layer)
		{
			curr_score += (token->type == RED_SUBSHELL);
			if (token->type == RED_SUBSHELL)
				skip_deeper_layers(&token, curr_layer);
			else
				++token;
		}
		record = bigger(record, curr_score);
		token = curr_token;
		next_cmd_block(&token, curr_layer, _NO);
		token += (token->content != NULL);
	}
	return (record);
}

/*REVIEW - deepest

	Returns the deepest layer in the token list.
	For:	 	ls && (ls && (ls && (ls))), the deepest layer is 3.
	Layer:		0,	   1,	  2,	 3,	   -1
*/
int	deepest(t_token *token)
{
	int		record;

	record = 0;
	while (token->content)
	{
		if (record < token->prior)
			record = token->prior;
		++token;
	}
	return (record + 1);
}

int	matrix_size(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		++i;
	return (i);
}
