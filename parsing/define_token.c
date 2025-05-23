/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:51:32 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/22 20:38:53 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h" 

// types:

// COMMAND = 0,
// ARGUMENT = 1,
// FILES = 2,
// RED_OUT = 3,
// RED_IN = 4,
// RED_O_APPEND = 5,
// HERE_DOC = 6,
// PIPE = 7,
// AND = 8,
// OR = 9,
// WILDCARD = 10,
// PARENTHESIS = 11

//			TO DEFINE IN TOKEN STRUCT
//	1) tipo di token
//	4) dare syntax error quando prima di una parentesi non e` 
// presente un operatore

int	and_or_pipe_parenthesis(t_token *tok, t_data *gen, int *id)
{
	(void)gen, (void)id;
	if (!ft_strncmp(tok->content, "&&", 2))
		tok->type = AND;
	else if (!ft_strncmp(tok->content, "||", 2))
		tok->type = OR;
	else if (!ft_strncmp(tok->content, "|", 1))
		tok->type = PIPE;
	else if (!ft_strncmp(tok->content, "(", 1))
		tok->type = PARENTHESIS;
	else if (!ft_strncmp(tok->content, ")", 1))
		tok->type = PARENTHESIS;
	return (0);
}

int	is_operator(t_token *t, t_data *gen, int *id, bool check)
{
	if ((*id) < gen->token_num && t->content && t->t_quote != 1)
	{
		if (check == true)
		{
			if (!ft_strncmp(t->content, "<", ft_strlen(t->content)) || \
			!ft_strncmp(t->content, ">", ft_strlen(t->content)) || \
			!ft_strncmp(t->content, "<<", ft_strlen(t->content)) || \
			!ft_strncmp(t->content, ">>", ft_strlen(t->content)))
				return (is_redirection(t, gen, id));
		}
		else
		{
			if (!ft_strncmp(t->content, "&&", ft_strlen(t->content)) || \
			!ft_strncmp(t->content, "||", ft_strlen(t->content)) || \
			!ft_strncmp(t->content, "|", ft_strlen(t->content)) || \
			!ft_strncmp(t->content, "(", ft_strlen(t->content)) || \
			!ft_strncmp(t->content, ")", ft_strlen(t->content)))
				return (and_or_pipe_parenthesis(t, gen, id));
		}
	}
	return (0);
}

int	define_token_arg(t_token *token, t_data *gen)
{
	int	id;

	id = 0;
	while (id < gen->token_num && token[id].content != NULL)
	{
		if (is_operator(&token[id], gen, &id, true) == 1)
			return (ft_error("syntax error near unexpected token 10", 2, gen,
					token[id].content), 1);
		else
			id++;
	}
	id = 0;
	while (id < gen->token_num && token[id].content != NULL)
	{
		if (is_operator(&token[id], gen, &id, false) == 1)
			return (ft_error("syntax error near unexpected token11", 2, gen,
					token[id].content), 1);
		else
			id++;
	}
	is_cmd(token, gen);
	return (0);
}

int	define_token_and_parenthesis(t_token *token, t_data *gen)
{
	int	i;
	int	id;

	(void)i;
	id = 0;
	while (token[id].content != NULL)
	{
		if (count_parenthesis(token, gen) == 1)
			return (ft_error("syntax error near parenthesis12", 2, \
			gen, ""), 1);
		if (prior_of_token(token, gen) == 1)
			return (1);
		id++;
	}
	if (define_token_arg(token, gen) == 1)
		return (1);
	return (0);
}
