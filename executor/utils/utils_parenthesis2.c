/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parenthesis2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:40:37 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/28 10:30:32 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
//REVIEW - goto_valid_block

	Go to the next && || valid block.
	&& block must be executed only if current exit code is 0.
	|| block must be executed only if current exit code is not 0.
	Parenthesis makes the search more complex, but the logic is just this.
*/
void	goto_valid_block(t_exec *exec, t_token **token)
{
	while ((exec->prior_layer != (*token)->prior || \
	((*token)->type != AND && (*token)->type != OR)) || \
	(((*token)->type == AND && *exec->exit_code != 0) || \
	((*token)->type == OR && *exec->exit_code == 0)))
	{
		if (exec->prior_layer > (*token)->prior)
			return ;
		if (!(*token)->content)
			return ;
		++(*token);
	}
}

/*
//REVIEW - tok_next

	When manage_parenthesis has finished, calls this to go to the next token.
	
//		1)	Exit from the parenthesis layer;
		2)	If its not a redirect_subshell, <(ls), go to next command block.
			redir_subshell are special cases because they are as follows:
			cat <(ls executor) <(ls parsing) && echo "done!""
			So you don't have to go to the next command block, but to the next
			token;
		3)	If the token is a && or ||, we have to wait for all children
			currently in the pid_list and go to the next valid command block;
		4)	If there were issues with opening a file, token cursor is
			advanced to the next token.
*/
void	token_out_parenthesis(t_exec *exec, t_token **token, bool process_sub)
{
	skip_deeper_layers(token, exec->prior_layer);
	if (process_sub == _NO)
	{
		next_cmd_block(token, exec->prior_layer, _NO);
	}
	if (((*token)->type == AND || (*token)->type == OR))
	{
		exec->curr_cmd += 1;
		wait_everyone(exec);
		exec->curr_cmd -= 1;
		goto_valid_block(exec, token);
	}
	if (exec->file_not_found && (*token)->content)
		++(*token);
}

/*
//REVIEW - tok_next

	Detect if there are any pipes until end or the next && or || token.

	If there are, builtin behaves differently (exit, cd, export/unset with
	argument stop working).
*/
bool	detect_pipe(t_token *token, int getfd, int layer)
{
	if (getfd)
		return (0);
	skip_deeper_layers(&token, layer);
	while (token->content && !is_exec_sep(token->type))
	{
		if (token->type == RED_SUBSHELL)
			skip_deeper_layers(&token, layer);
		else
			++token;
	}
	if (token->type == PIPE)
		return (1);
	return (0);
}

/*REVIEW - check_proc_sub

	Checks if there are process substitution token without commands.
	Example of wrong prompts are:

	- <(ls)
	- cat | <(ls)
	- (cat) <(ls)

	Process substitution must be inside command block with commands,
	and in the same layer as the commmand block.
*/
bool	check_proc_sub(t_exec *exec, t_token *token)
{
	int		cmd;
	int		cmd_layer;

	cmd = 0;
	while (cmd != exec->last_cmd)
	{
		cmd_layer = -1;
		while (token->content)
		{
			if (token->type == COMMAND && token->cmd_num == cmd)
			{
				cmd_layer = token->prior;
			}
			if (token->type == RED_SUBSHELL && token->cmd_num == cmd)
			{
				if (token->prior != cmd_layer)
					return (set_exit_code(exec, 126), 1);
			}
			++token;
		}
		token = exec->first_token;
		++cmd;
	}
	return (0);
}
