/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:48:14 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/08 11:40:24 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	pipe_infront_or_back(t_token *token, t_data *gen)
{
	int	last;

	last = gen->token_num - 1;
	if (token[0].type == PIPE || token[0].type == AND || token[0].type == OR)
		return (ft_error("syntax error near unexpected token", 2, gen,
				token[0].content) ,1);
	else if (token[last].type == PIPE || token[last].type == AND ||
		token[last].type == OR)
		return (ft_error("syntax error near unexpected token", 2, gen,
				token[last].content) ,1);
	return (0);
}

int	redirection_heredoc_valid(t_token *token, t_data *gen)
{
	int	id;

	id = 0;
	(void)gen;
	while (token[id].content != NULL)
	{
		if ((token[id].type == RED_IN || token[id].type == RED_OUT)
			&& token[id + 1].content)
		{
			if (token[id + 1].type != FILES && token[id + 1].type != PARENTHESIS)
				return (ft_error("syntax error near unexpected token ", 2, gen,
				token[id].content) ,1);
		}
		if ((token[id].type == RED_O_APPEND || token[id].type == HERE_DOC)
			&& token[id + 1].content)
		{
			if (token[id + 1].type != FILES)
				return (ft_error("syntax error near unexpected token ", 2, gen,
				token[id].content) ,1);
		}
		id++;
	}
	return (0);
}

// ritorna 1 per syntax error
int	actual_parser(t_token *token, t_data *gen)
{
	if (pipe_infront_or_back(token, gen) == 1)
		return (1);
	if (redirection_heredoc_valid(token, gen) == 1)
		return (1);
	return (0);
}
