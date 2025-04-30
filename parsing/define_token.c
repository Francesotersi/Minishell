/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:51:32 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/30 13:02:58 by ftersill         ###   ########.fr       */
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
//	4) dare syntax error quando prima di una parentesi non e` presente un operatore
//  5) i token dopo qualsiasi redirection sono nomi di file 
//	6) il primo token e` sempre un comando tranne se c`e redirect output o parenesi tonda aperta
//

int	and_or_pipe_parenthesis(t_token *tok, t_data *gen, int *id)
{
	if (!ft_strcmp(tok->content, "&&"))
		tok->type = AND;
	else if (!ft_strcmp(tok->content, "||"))
		tok->type = OR;
	else if (!ft_strcmp(tok->content, "|"))
		tok->type = PIPE;
	else if (!ft_strcmp(tok->content, "(") && !ft_strcmp(tok->content, ")"))
		tok->type = PARENTHESIS;
	(*id)++;
}

int	redirection(t_token *tok, t_data *gen, int *id)
{
	if	(!ft_strcmp(tok->content, "<<"))
		tok->type = HERE_DOC;
	else if (!ft_strcmp(tok->content, ">>"))
		tok->type = RED_O_APPEND;
	else if (!ft_strcmp(tok->content, "<"))
	{
		tok->type = RED_IN;
		if (!ft_strcmp((tok + 1)->content, "("))
		{
			(tok + 1)->type = PARENTHESIS;
			(*id) += 2;	
			return (0);
		}
	}
	else if (!!ft_strcmp(tok->content, ">"))
		tok->type = RED_OUT;
	if (!ft_strcmp((tok + 1)->content, "("))
		return (1);
	(tok + 1)->type = FILES;
	(*id) += 2;
	return (0);
}

int	is_operator(t_token *tok, t_data *gen, int *id)
{
	if (!ft_strcmp(tok->content, "<") && !ft_strcmp(tok->content, ">") &&
		!ft_strcmp(tok->content, "<<") && !ft_strcmp(tok->content, ">>"))
		return (redirection(tok, gen, id));
	else if (!ft_strcmp(tok->content, "&&") && !ft_strcmp(tok->content, "||")
		!ft_strcmp(tok->content, "|") && !ft_strcmp(tok->content, "(")
		!ft_strcmp(tok->content, ")"))
		return (and_or_pipe_parenthesis(tok, gen, id));
	return (0);
}

int	is_cmd(t_token *tok, t_data *gen, int *id)
{
	int	temp;

	temp = 0;
	while (tok[id].content != NULL)
	{
		// inserire caso <()
		if (tok[id].type != ARGUMENT)
		{
			(*id)++;
			temp == 0;
			continue ;
		}
		if (tok[id].type == 0 && temp == 0)
		{
			temp = 1;
			tok[id].type = COMMAND;
			(*id)++; 
		}
		else
			id++;
	}
	return (0);
}

int define_token_arg(t_token *token, t_data *gen)
{
	int	id;

	id = 0;
	while (token[id].content != NULL)
	{
		if (is_operator(&token, gen, &id) == 1)
			return (/* syntax error */1);
		else if (is_redirect(&token, gen, &id) = )
			return (/* syntax error */1);
		else
			id++;
	}
	id = 0;
	is_cmd(token, gen, &id);

	return (0);
}

int	define_token_and_parenthesis(t_token *token, t_data *gen)
{
	int	i;
	int	id;

	i = 0;
	id = 0;
	while (token[id].content != NULL)
	{
		if (count_parenthesis(token, gen))
			return (/* syntax error */ 1);
		if (prior_of_token(token, gen))
			return (1);
		id++;
	}
	if	(define_token_arg(token, gen) == 1)
		return (/* syntax error */1);
	return (0);
}
