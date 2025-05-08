/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:40:44 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/06 16:37:57 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	next_cmd_block(t_token **token, int layer, bool accept_deeper_token)
{
	while ((*token)->content)
	{
		if (accept_deeper_token)
		{
			if (layer <= (*token)->prior && is_exec_sep((*token)->type) == _NO)
				++(*token);
			else
				break ;
		}
		else
		{
			if (layer == (*token)->prior && (*token)->type == RED_SUBSHELL)
				break ;
			if (layer == (*token)->prior && is_exec_sep((*token)->type) == _NO)
				++(*token);
			else
				break ;
		}
	}
}

void	skip_deeper_layers(t_token **token, int layer)
{
	if ((*token)->type == RED_SUBSHELL)
		(*token) += 1;
	while ((*token)->content && (*token)->prior > layer)
		++(*token);
}

int	count_in_layer(t_token *token, int layer)
{
	int	counter;

	counter = 0;
	while (token->prior >= layer)
	{
		if (token->prior != layer)
			skip_deeper_layers(&token, layer);
		else
			++counter;
		if (token->content)
			++token;
	}
	return (counter);
}

int	cmd_block_len(t_token *token, int layer)
{
	int	counter;

	counter = 0;
	while (token->prior >= layer)
	{
		if (token->prior != layer)
			skip_deeper_layers(&token, layer);
		if (token->content)
			++token;
	}
	return (counter);
}
