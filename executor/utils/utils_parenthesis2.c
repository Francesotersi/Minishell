/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parenthesis2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:40:37 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/04 16:29:47 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	goto_valid_block(t_exec *exec, t_token **token)
{
	while ((exec->prior_layer != (*token)->prior || \
	((*token)->type != AND && (*token)->type != OR)) || \
	(((*token)->type == AND && *exec->exit_status != 0) || \
	((*token)->type == OR && *exec->exit_status == 0)))
	{
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
