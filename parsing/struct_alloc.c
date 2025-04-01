/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:22:31 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/01 11:57:46 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// qua da risdcrivere la parte delle quotes perche 1) conta male, 2)seie gay sium! 

int	string_allocation(t_token *token, int counter, int *token_id)
{
	if (counter != 0)
	{
		token[(*token_id)].str = malloc(sizeof(char) * counter);
		if (!token[(*token_id)].str)
			return (write(2, "bash: allocation error\n", 24), 1);
		token->id = (*token_id);
		(*token_id)++;
		printf("token numero = %d; allocato di %d\n", *token_id, counter);
	}
	return (0);
}

int	alloc_quotes_token(t_token *token, t_data *gen, int *i, int *counter)
{
	if (gen->input[*i] == '\"')
	{
		while (gen->input[++(*i)] != '\"' && gen->input[*i] != '\0')
			(*counter)++;
		(*i)++;
		alloc_quotes_token(token, gen, i, counter);
		return (0);
	}
	if (gen->input[*i] == '\'')
	{
		while (gen->input[++(*i)] != '\'' && gen->input[*i] != '\0')
			(*counter)++;
		(*i)++;
		alloc_quotes_token(token, gen, i, counter);
		return (0);
	}
	return (2);
}

int	alloc_operator_token(t_token *token, t_data *gen, int *i, int *token_id)
{
	int	counter;

	counter = 0;
	while ((gen->input[*i] == '>' || gen->input[*i] == '<' \
		|| gen->input[*i] == '&' || gen->input[*i] == '|' \
		|| gen->input[*i] == '(' || gen->input[*i] == ')') \
		&& gen->input[*i] != '\0')
	{
		if ((gen->input[*i] == '<' && gen->input[*i + 1] == '<') || \
				(gen->input[*i] == '>' && gen->input[*i + 1] == '>') || \
				(gen->input[*i] == '&' && gen->input[*i + 1] == '&') || \
				(gen->input[*i] == '|' && gen->input[*i + 1] == '|'))
		{
			(*i) += 2;
			counter += 2;
			break ;
		}
		else
			counter += 1;
		(*i)++;
		break ;
	}
	if (string_allocation(token, counter, token_id) == 1)
		return (1);
	return (0);
}

int	alloc_char_token(t_token *token, t_data *gen, int *i, int *token_id)
{
	int counter;

	counter = 0;
	while (gen->input[*i] != '&' && gen->input[*i] != '|' \
		&& gen->input[*i] != '<' && gen->input[*i] != '>' \
		&& gen->input[*i] != ' ' && gen->input[*i] != '(' \
		&& gen->input[*i] != ')' && gen->input[*i] != '\0')
	{
		if (alloc_quotes_token(token, gen, i, &counter) == 0)
			continue ;
		(*i)++;
		counter++;
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
	token_id = 0;;
	while (gen->input[i] != '\0')
	{
		while (gen->input[i] != '\0' && gen->input[i] == ' ')
			i++;
		if (alloc_char_token(token, gen, &i, &token_id) == 1)
			return (write(2, "alloc error\n", 12), 1);
		if (alloc_operator_token(token, gen, &i, &token_id) == 1)
			return (write(2, "alloc error\n", 12), 1);
	}
	return (0);
}
