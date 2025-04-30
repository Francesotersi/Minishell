/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:24:35 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/29 14:35:35 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*REVIEW - count_commands

//	Count the number of command block in the commands line sent by parsing.
	exec allocation size depend on this number.
	Checks if there are pipe on the commands line.
*/
int	count_commands(t_exec *exec, t_token *tokens)
{
	int	cmd_num;
	int	pipe_num;

	cmd_num = 0;
	pipe_num = 0;
	while (tokens->content != NULL)
	{
		pipe_num += (tokens->type == PIPE);
		cmd_num += (tokens->type == COMMAND);
		++tokens;
	}
	exec->at_least_one_pipe = pipe_num > 0;
	return (cmd_num);
}

int	find_command_argument_index(t_exec *exec, t_token *token)
{
	t_token	*current;
	int		cmd_argc;

	current = token;
	cmd_argc = 0;
	while (token->id != 0 && \
		(token->prior >= (token - 1)->prior || \
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
			while (token != current && exec->prior_layer != (token + 1)->prior)
				++token;
			++cmd_argc;
		}
		else if (token->type == ARGUMENT)
			++cmd_argc;
		++token;
	}
	return (cmd_argc);
}

void	find_command_id(t_exec *exec, t_token *token)
{
	while (token->id != 0 && token->cmd_num != (token - 1)->cmd_num)
		--token;
	while ("Loop until you find the command id")
	{
		if (token->type == COMMAND)
		{
			exec->curr_cmd = token->id;
			break ;
		}
		++token;
		if (token->cmd_num != (token - 1)->cmd_num)
		{
			exec->curr_cmd = -1;
			break ;
		}
	}
}

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
