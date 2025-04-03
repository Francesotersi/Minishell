/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:38:38 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/03 14:12:18 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// allora funziona il fill ma se usi un operatore hai un uniunistialized value che dovresti togliere in qualche modo ricordatio di controllare daiiii coglione

int	copy_operator_fill(t_token *token, t_data *gen, int *i)
{
	int	roll;

	roll = 0;
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
			token->str[roll++] = gen->input[(*i)++];
			token->str[roll++] = gen->input[(*i)++];
		}
		else
			token->str[roll++] = gen->input[(*i)++];
		return (0);
	}
	return (2);
}

int	copy_quotes_fill(t_token *token, t_data *gen, int *i, int *roll)
{
	if (gen->input[*i] == '\"')
	{
		(*i)++;
		while (gen->input[*i] != '\"' && gen->input[*i] != '\0')
			token->str[(*roll)++] = gen->input[(*i)++];
		(*i)++;
		if (gen->input[*i] == '\"' || gen->input[*i] == '\'')
			copy_quotes_fill(token, gen, i, roll);
		else
			return (0);
	}
	if (gen->input[*i] == '\'')
	{
		(*i)++;
		while (gen->input[*i] != '\'' && gen->input[*i] != '\0')
			token->str[(*roll)++] = gen->input[(*i)++];
		(*i)++;
		if (gen->input[*i] == '\"' || gen->input[*i] == '\'')
			copy_quotes_fill(token, gen, i, roll);
		else
			return (0);
	}
	return (2);
}

int	copy_char_fill(t_token *token, t_data *gen, int *i)
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
		else
			token->str[roll++] = gen->input[(*i)++];
	}
	if (roll != 0)
	{
		token->str[roll] = '\0';
		return (0);
	}
	return (2);
}

void	fill_struct(t_token *token, t_data *gen)
{
	int	token_id;
	int i;

	i = 0;
	token_id = 0;
	while (gen->input[i] != '\0')
	{
		while (gen->input[i] == ' ' && gen->input[i] != '\0')
			i++;
		if (copy_char_fill(&token[token_id], gen, &i) == 0 \
			&&  i < (int)ft_strlen(gen->input))
		{
			if (gen->input[i + 1] && gen->input[i + 1] == ' ')
				token[token_id].space_on_right = true;
		}
		else if (copy_operator_fill(&token[token_id], gen, &i) == 0 \
			&&  i < (int)ft_strlen(gen->input))
		{
			if (gen->input[i + 1] && gen->input[i + 1] == ' ')
				token[token_id].space_on_right = true;
		}
		token_id++;
	}
}
