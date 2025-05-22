/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:38:38 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/20 15:16:04 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// il conteggio dei numero e` sbagliato quando sono presenti quote singole e 
// doppie una dopo l`altra senza spazi in mezzo

int	copy_operator_fill(t_token *token, t_data *gen, int *i)
{
	int	roll;

	roll = 0;
	if ((gen->input[*i] == '&' || gen->input[*i] == '|' || \
		gen->input[*i] == '(' || gen->input[*i] == ')' || \
		gen->input[*i] == '>' || gen->input[*i] == '<') && \
		gen->input[*i] != '\0')
	{
		if ((gen->input[*i] == '&' && gen->input[*i + 1] == '&') || \
			(gen->input[*i] == '|' && gen->input[*i + 1] == '|') || \
			(gen->input[*i] == '>' && gen->input[*i + 1] == '>') || \
			(gen->input[*i] == '<' && gen->input[*i + 1] == '<'))
		{
			token->content[roll++] = gen->input[(*i)++];
			token->content[roll++] = gen->input[(*i)++];
		}
		else
			token->content[roll++] = gen->input[(*i)++];
		return (0);
	}
	return (1);
}

int	copy_quotes_fill(t_token *token, t_data *gen, int *i, int *roll)
{
	if (gen->input[(*i)] == '\"' && gen->input[(*i)] != '\0')
	{
		token->content[(*roll)++] = gen->input[(*i)];
		while (gen->input[++(*i)] != '\"' && gen->input[(*i)] != '\0')
			token->content[(*roll)++] = gen->input[(*i)];
		if (gen->input[(*i)] == '\"' && gen->input[(*i)] != '\0')
			token->content[(*roll)++] = gen->input[(*i)++];
		return (1);
	}
	if (gen->input[(*i)] == '\'' && gen->input[(*i)] != '\0')
	{
		token->content[(*roll)++] = gen->input[(*i)];
		while (gen->input[++(*i)] != '\'' && gen->input[(*i)] != '\0')
			token->content[(*roll)++] = gen->input[(*i)];
		if (gen->input[(*i)] == '\'' && gen->input[(*i)] != '\0')
			token->content[(*roll)++] = gen->input[(*i)++];
		return (1);
	}
	return (0);
}

int	copy_char_fill(t_token *token, t_data *gen, int *i)
{
	int	roll;

	roll = 0;
	while (gen->input[(*i)] != '&' && gen->input[(*i)] != '|' && \
	gen->input[(*i)] != '(' && gen->input[(*i)] != ')' && \
	gen->input[(*i)] != '>' && gen->input[(*i)] != '<' && \
	gen->input[(*i)] != ' ' && gen->input[(*i)] != '\0')
	{
		if (copy_quotes_fill(token, gen, i, &roll) == 1)
			continue ;
		else
			token->content[roll++] = gen->input[(*i)++];
	}
	if (!roll)
		return (1);
	return (0);
}

// riempie la struttura dei token e una volta finito rimuove le quotes
// correttamente e espande le variabili di ambiente e exit status
void	fill_struct(t_token *token, t_data *gen)
{
	int	token_id;
	int	i;

	i = 0;
	token_id = 0;
	while (gen->input[i] != '\0' && token_id < gen->token_num)
	{
		while (gen->input[i] == ' ' && gen->input[i] != '\0')
			i++;
		if (!copy_operator_fill(&token[token_id], gen, &i))
		{
			if (gen->input[i] && gen->input[i] == ' ')
				token[token_id].space_on_right = true;
			token[token_id].id = token_id;
			token_id++;
		}
		if (!copy_char_fill(&token[token_id], gen, &i))
		{
			if (gen->input[i] && gen->input[i] == ' ')
				token[token_id].space_on_right = true;
			token[token_id].id = token_id;
			token_id++;
		}
	}
}
