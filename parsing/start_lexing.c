/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_lexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:05:20 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/28 10:46:09 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	operator_token(char *str, int *i, int *len, t_data *gen)
{
	while ((str[*i] == '>' || str[*i] == '<' || str[*i] == '&' \
		|| str[*i] == '|' || str[*i] == '(' || str[*i] == ')') \
		&& str[*i] != '\0')
	{
		if ((str[*i] == '<' && str[*i + 1] == '<' && str[*i + 2] == '<') || \
			(str[*i] == '>' && str[*i + 1] == '>' && str[*i + 2] == '>'))
			return (ft_error("syntax error near	operator", 2, gen, ""), 1);
		if ((str[*i] == '<' && str[*i + 1] == '>') || \
				(str[*i] == '>' && str[*i + 1] == '<' ) || \
				(str[*i] == '&' && str[*i + 1] != '&') || \
				(str[*i] == '|' && str[*i + 1] == '|' && str[*i + 2] == '|'))
			return (ft_error("syntax error near	operator", 2, gen, ""), 1);
		else if ((str[*i] == '<' && str[*i + 1] == '<') || \
				(str[*i] == '>' && str[*i + 1] == '>') || \
				(str[*i] == '&' && str[*i + 1] == '&') || \
				(str[*i] == '|' && str[*i + 1] == '|'))
		{
			(*i)++;
			(*len)++;
		}
		else
			(*len)++;
		(*i)++;
	}
	return (0);
}

// gestisce le quotes
int	quotes_token(char *str, int *i, int *len, int *temp)
{
	(void)temp;
	if (str[(*i)] == '\"' && str[(*i)] != '\0')
	{
		(*len)++;
		while (str[++(*i)] != '\"' && str[(*i)] != '\0')
			;
		if (str[(*i)] == '\0')
			return (2);
		if (str[(*i)] == '\"')
			(*i)++;
		return (1);
	}
	if (str[(*i)] == '\'' && str[(*i)] != '\0')
	{
		(*len)++;
		while (str[++(*i)] != '\'' && str[(*i)] != '\0')
			;
		if (str[(*i)] == '\0')
			return (2);
		if (str[(*i)] == '\'')
			(*i)++;
		return (1);
	}
	return (0);
}

int	count_char_token(char *str, int *i, int *len, t_data *gen)
{
	int	temp;
	int	temp2;

	temp = 0;
	temp2 = 0;
	while (str[*i] != '&' && str[*i] != '|' && str[*i] != '<' \
	&& str[*i] != '>' && str[*i] != ' ' && str[*i] != '(' \
	&& str[*i] != ')' && str[*i] != '\0')
	{
		temp2 = quotes_token(str, i, len, &temp);
		if (temp2 == 2)
			return (ft_error("syntax error near	quote", 2, gen, ""), 1);
		else if (temp2 == 1)
			continue ;
		else if (temp == 0 && str[*i])
		{
			(*len)++;
			temp = 1;
		}
		if (str[*i])
			(*i)++;
	}
	return (0);
}

//		to-do list:
//	X) Allocare la stringa
//	X) riempire la struttura con le stringhe
//  3) fare controlli per il parsing effettivo
//
//		casi limite
//
// 		RICORDA!
// 	RITORNA 2 PER DARE SYNTAX ERROR (exit_code = 2)
int	start_lexing_2(t_data *gen, int j, t_token **token)
{
	j = intersection(*token, gen);
	if (j == 1)
	{
		*token = reallocation_and_all(gen, *token);
		if (!*token)
			return (free_all(*token, gen, true), 2);
	}
	else if (j == 2)
		return (free_all(*token, gen, true), 2);
	if (define_token_and_parenthesis(*token, gen) == 1)
		return (free_all(*token, gen, true), 2);
	if (actual_parser(*token, gen) == 1)
		return (free_all(*token, gen, true), 2);
	return (0);
}

int	start_lexing(t_data *gen, int j)
{
	t_token			*token;

	if (command_substitution(&gen->input, gen) != 0)
		return (2);
	gen->token_num = num_token(gen->input, gen);
	if (gen->token_num == 0)
		return (2);
	token = (t_token *)ft_calloc(sizeof(t_token), gen->token_num + 1);
	if (!token)
		return (write(2, "bash: malloc error\n", 14), 1);
	(*token) = (t_token){0};
	if (alloc_str_token(token, gen) == 1)
		return (1);
	if (start_lexing_2(gen, j, &token) == 2)
		return (2);
	gen->token = token;
	return (0);
}
