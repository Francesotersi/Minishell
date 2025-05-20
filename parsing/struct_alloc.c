/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:22:31 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/20 09:13:59 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// qua da risdcrivere la parte delle quotes perche 1) conta male

int	string_allocation(t_token *tok, int index, int *token_id)
{
	if (index)
	{
		tok[(*token_id)].content = (char *)ft_calloc(sizeof(char), index + 1);
		if (!tok[(*token_id)].content)
			return (write(2, "bash: allocation error\n", 23), 1);
		(*token_id)++;
	}
	return (0);
}

// g = gen accorciato perche le colonne superavano di 80
int	alloc_operator_token(t_token *token, t_data *gen, int *i, int *token_id)
{
	int	counter;

	counter = 0;
	if (gen->input[*i] == '&' || gen->input[*i] == '|' || \
		gen->input[*i] == '(' || gen->input[*i] == ')' || \
		gen->input[*i] == '>' || gen->input[*i] == '<')
	{
		if ((gen->input[*i] == '&' && gen->input[*i + 1] == '&') || \
			(gen->input[*i] == '|' && gen->input[*i + 1] == '|') || \
			(gen->input[*i] == '>' && gen->input[*i + 1] == '>') || \
			(gen->input[*i] == '<' && gen->input[*i + 1] == '<'))
		{
			counter = 2;
			*i += 2;
		}
		else
		{
			counter = 1;
			*i += 1;
		}
		if (string_allocation(token, counter, token_id) == 1)
			return (1);
	}
	return (0);
}

int	alloc_quotes_token(t_data *gen, int *i, int *counter)
{
	if (gen->input[(*i)] == '\"')
	{
		(*counter)++;
		while (gen->input[++(*i)] != '\"' && gen->input[(*i)] != '\0')
			(*counter)++;
		if (gen->input[(*i)] == '\"')
		{
			(*i)++;
			(*counter)++;
		}
		return (1);
	}
	if (gen->input[(*i)] == '\'')
	{
		(*counter)++;
		while (gen->input[++(*i)] != '\'' && gen->input[(*i)] != '\0')
			(*counter)++;
		if (gen->input[(*i)] == '\'')
		{
			(*i)++;
			(*counter)++;
		}
		return (1);
	}
	return (0);
}

int	alloc_char_token(t_token *token, t_data *gen, int *i, int *token_id)
{
	int	counter;

	counter = 0;
	while (gen->input[(*i)] != '&' && gen->input[(*i)] != '|' && \
	gen->input[(*i)] != '(' && gen->input[(*i)] != ')' && \
	gen->input[(*i)] != '>' && gen->input[(*i)] != '<' && \
	gen->input[(*i)] != ' ' && gen->input[(*i)] != '\0')
	{
		if (alloc_quotes_token(gen, i, &counter) == 1)
			continue ;
		else
		{
			(*i)++;
			counter++;
		}
	}
	if (string_allocation(token, counter, token_id) == 1)
		return (1);
	return (0);
}

//	conta la lunghezza di ogni token cosi da poter poi allocare la stringa
int	alloc_str_token(t_token *token, t_data *gen)
{
	int	i;
	int	token_id;

	i = 0;
	token_id = 0;
	while (gen->input[i] != '\0')
	{
		while (gen->input[i] != '\0' && gen->input[i] == ' ')
			i++;
		if (alloc_char_token(token, gen, &i, &token_id) == 1)
			return (1);
		if (alloc_operator_token(token, gen, &i, &token_id) == 1)
			return (1);
	}
	return (0);
}
