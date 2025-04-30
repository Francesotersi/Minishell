/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:40:44 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/28 19:23:03 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	next_token(t_token **token, int search1, int search2, int search3)
{
	while ((*token)->content)
	{
		if ((*token)->type != search1 && \
		(*token)->type != search2 && \
		(*token)->type != search3)
			++(*token);
		else
			break ;
	}
}

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
			if (layer == (*token)->prior && is_exec_sep((*token)->type) == _NO)
				++(*token);
			else
				break ;
		}
	}
}

void	skip_deeper_layers(t_token **token, int layer)
{
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
