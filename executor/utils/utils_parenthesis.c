/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:40:44 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/19 17:59:23 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
//REVIEW - lowest_cmd_block

	Search for the next token that is a execution separator (&&, ||, |).

	If accept_deeper_token is true, we stop if the token has less priority
	that the execution layer (when we exit from a parenthesis: (ls) && echo ok
	when we hit &&).
	If accept_deeper_token is false, we stop if the token has the same
	priority as the execution layer.
*/
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
	while ((*token)->content && is_exec_sep((*token)->type) == _NO && \
		(*token)->type != RED_SUBSHELL)
		++(*token);
}

/*
//REVIEW - tok_next

	Go to the next token of type chr in the token list.
	
	If accept_deeper_token is true, we go on until the token has less priority
	that the execution layer (when we exit from a parenthesis: (ls) && echo ok
	when we hit &&).
	If accept_deeper_token is false, we go on until the token has the same
	priority as the execution layer or is a execution separator.
*/
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

/*
//REVIEW - skip_deeper_layers

	Search the next token that is in a valid parenthesis layer.
	We scroll the token list until we find a token with the same priority as
	layer.
	If current is the start of a redirect_subshell, <(, we skip it
	to enter in the parenthesis.
*/
void	skip_deeper_layers(t_token **token, int layer)
{
	if ((*token)->type == RED_SUBSHELL)
		(*token) += 1;
	while ((*token)->content && (*token)->prior > layer)
		++(*token);
}

/*
//REVIEW - count_in_layer

	Return the number of tokens in a layer, excluding parenthesis.
*/
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

/*
//REVIEW - cmd_block_len

	Return the lenght of a command block, excluding parenthesis.
*/
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
