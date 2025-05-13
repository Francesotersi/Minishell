/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parenthesis2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:40:37 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/12 16:58:56 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

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

void	tok_next(t_token **token, int chr, int layer, bool accept_deeper_tok)
{
	while ((*token)->content)
	{
		if (accept_deeper_tok)
		{
			if (layer <= (*token)->prior && (*token)->type != chr)
				++(*token);
			else
				break ;
		}
		else
		{
			if (layer == (*token)->prior && (*token)->type != chr)
				++(*token);
			else
				break ;
		}
	}
}

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
	if (exec->file_not_found)
		++(*token);
}

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
