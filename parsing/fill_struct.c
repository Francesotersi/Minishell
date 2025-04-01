/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:38:38 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/01 12:44:50 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	copy_quotes_fill(t_token *token, t_data *gen, int *i, int *roll)
{
	if (gen->input[*i] == '\"')
	{
		while (gen->input[++(*i)] != '\"' && gen->input[*i] != '\0')
			token->str[(*roll)++] = gen->input[*i];
		(*i)++;
		copy_quotes_fill(token, gen, i, roll);
		return (0);
	}
	if (gen->input[*i] == '\'')
	{
		while (gen->input[*i] != '\'' && gen->input[*i] != '\0')
			token->str[(*roll)++] = gen->input[(*i)++];
		(*i)++;
		copy_quotes_fill(token, gen, i, roll);
		return (0);
	}
	return (2);
}

void	copy_char_fill(t_token *token, t_data *gen, int *i)
{
	int	roll;

	roll = 0;
	while (gen->input[*i] != '&' && gen->input[*i] != '|' \
		&& gen->input[*i] != '<' && gen->input[*i] != '>' \
		&& gen->input[*i] != ' ' && gen->input[*i] != '(' \
		&& gen->input[*i] != ')' && gen->input[*i] != '\0')
	{
		if (copy_quotes_fill(token, gen, i, &roll) == 0)
			continue ;
		token->str[roll++] = gen->input[(*i)++];
		// aggiungere qua la parte per la conta degli spazi a destra del token
	}
}

// se dai un input con spazi o piu di un token rimane aperto da qualche parte fixalo coglione
void	fill_struct(t_token *token, t_data *gen)
{
	int	token_id;
	int i;

	i = 0;
	token_id = 0;
	while (gen->input[i] == ' ' && gen->input[i] != '\0')
		i++;
	while (gen->input[i] != '\0')
	{
		copy_char_fill(&token[token_id], gen, &i);
		// copy_operator_fill(token[token_id], gen->input, &i, &token_id);
		token_id++;
	}
	printf_struct(token, gen);
}
