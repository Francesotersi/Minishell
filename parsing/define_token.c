/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:51:32 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/05 14:08:35 by ftersill         ###   ########.fr       */
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

int	is_operator(t_token *tok, t_data *gen, int *id)
{
	if ((*id) < gen->token_num && tok->content)
	{
		if (!ft_strncmp(tok->content, "<", ft_strlen(tok->content)) ||
		!ft_strncmp(tok->content, ">", ft_strlen(tok->content)) ||
		!ft_strncmp(tok->content, "<<", ft_strlen(tok->content)) ||
		!ft_strncmp(tok->content, ">>", ft_strlen(tok->content)))
			return (is_redirection(tok, gen, id));
		else if (!ft_strncmp(tok->content, "&&", ft_strlen(tok->content)) ||
		!ft_strncmp(tok->content, "||", ft_strlen(tok->content)) ||
		!ft_strncmp(tok->content, "|", ft_strlen(tok->content)) ||
		!ft_strncmp(tok->content, "(", ft_strlen(tok->content)) ||
		!ft_strncmp(tok->content, ")", ft_strlen(tok->content)))
			return (and_or_pipe_parenthesis(tok, gen, id));
	}
	return (0);
}

int	is_cmd(t_token *tok, t_data *gen)
{
	int	id;

	id = 0;
	while (tok[id].content != NULL)
	{
		while (id < gen->token_num && tok[id].type != ARGUMENT)
			id++;
		if (tok[id].type == ARGUMENT)
			tok[id++].type = COMMAND;
		while (id < gen->token_num && tok[id].type == ARGUMENT)
			id++;
		while (id < gen->token_num && (tok[id].type != PIPE ||
		tok[id].type != AND || tok[id].type != OR) && tok[id].type != ARGUMENT)
			id++;
	}
	return (0);
}

int define_token_arg(t_token *token, t_data *gen)
{
	int	id;

	id = 0;
	while (id < gen->token_num && token[id].content != NULL)
	{
		if (is_operator(&token[id], gen, &id) == 1)
			return (/* syntax */1);
		else
			id++;
	}
	is_cmd(token, gen);
	return (0);
}

// 									RICORDA!
// POTREBBE DARE PROBLEMI IL CASO ls <(ls) -R PERCHE IL -R NON VIENE FLAGGATO CORRETTAMENTE
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
