/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:48:14 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/14 12:42:30 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// to do checks
// prima delle parentesi ci deve essere un AND OR o PIPE
// echo "*redirection" sbagli a flaggare la redirection come ARGOMENTO
// e non dai syntax quando piu rediredtion sono una dietro l`altrra perche
// sbagli a flaggare probilmente 

int	pipe_infront_or_back(t_token *token, t_data *gen)
{
	int	last;

	last = gen->token_num - 1;
	if (token[0].type == PIPE || token[0].type == AND || token[0].type == OR)
		return (ft_error("syntax error near unexpected token8", 2, gen,
				token[0].content), 1);
	else if (token[last].type == PIPE || token[last].type == AND || \
		token[last].type == OR)
		return (ft_error("syntax error near unexpected token9", 2, gen,
				token[last].content), 1);
	return (0);
}

int	redirection_heredoc_valid(t_token *token, t_data *gen)
{
	int	id;

	id = 0;
	while (token[id].content != NULL)
	{
		if ((token[id].type == RED_IN || token[id].type == RED_OUT)
			&& token[id + 1].content)
		{
			if (token[id + 1].type != FILES
				&& token[id + 1].type != PARENTHESIS)
				return (ft_error("syntax error near unexpected token 6", 2, gen
						, token[id].content), 1);
		}
		if ((token[id].type == RED_O_APPEND || token[id].type == HERE_DOC)
			&& token[id + 1].content)
		{
			if (token[id + 1].type != FILES)
				return (ft_error("syntax error near unexpected token 7", 2, gen
						, token[id].content), 1);
		}
		id++;
	}
	return (0);
}

int	more_cases(t_token *tok, int *id, t_data *gen)
{
	if ((tok[(*id)].type == RED_IN || tok[(*id)].type == RED_OUT)
		&& tok[(*id) + 1].content)
	{
		if (!ft_strncmp(tok[(*id) + 1].content, ")", \
			ft_strlen(tok[(*id) + 1].content)))
			return (ft_error("syntax error near unexpected token 5", 2,
					gen, tok[(*id) + 1].content), 1);
	}
	if (!ft_strncmp(tok[(*id)].content, "(", ft_strlen(tok[(*id)].content))
		&& tok[(*id) + 1].content)
	{
		if (tok[(*id) + 1].type != AND && tok[(*id) + 1].type != OR
			&& tok[(*id) + 1].content[0] != '(' && \
			tok[(*id) + 1].type != COMMAND)
			return (ft_error("syntax error near unexpected token 4", 2,
					gen, tok[(*id) + 1].content), 1);
	}
	if (even_more_cases(tok, id, gen) == 1)
		return (1);
	return (0);
}

// Controlla che dopo && ci sia un comando valido (non un ")" o un operatore).
// il numero 5 = a red_o_append
int	valid_parenthesis_and_or(t_token *tok, t_data *gen)
{
	int	id;

	id = 0;
	while (tok[id].content != NULL)
	{
		if (!ft_strncmp(tok[id].content, "(", ft_strlen(tok[id].content))
			&& tok[id + 1].content)
			if (!ft_strncmp(tok[id + 1].content, ")", \
				ft_strlen(tok[id + 1].content)))
				return (ft_error("syntax error near unexpected token 1", 2,
						gen, tok[id].content), 1);
		if ((tok[id].type == AND || tok[id].type == OR) && tok[id + 1].content)
		{
			if (tok[id + 1].content[0] != '(' && tok[id + 1].type != COMMAND
				&& tok[id + 1].type != RED_OUT && tok[id + 1].type != RED_IN
				&& tok[id + 1].type != HERE_DOC && tok[id + 1].type != 5)
				return (ft_error("syntax error near unexpected token 2", 2,
						gen, tok[id].content), 1);
		}
		if (more_cases(tok, &id, gen) == 1)
			return (1);
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
	if (valid_parenthesis_and_or(token, gen) == 1)
		return (1);
	return (0);
}
