/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:08:56 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/27 15:56:36 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	actual_removal_2(t_token *token, char *temp, int *i, int *j)
{
	if (temp[(*i)] && temp [(*i)] == '\\' && temp[(*i) + 1] && \
		(temp[(*i) + 1] == '\"' || temp[(*i) + 1] == '\''))
	{
		(*i)++;
		token->content[(*j)++] = temp[(*i)];
		return (1);
	}
	token->content[(*j)++] = temp[(*i)++];
	return (0);
}

void	fill_input(t_data *gen, t_token *token)
{
	int	i;
	int	id;
	int	j;

	id = 0;
	j = 0;
	while (token[id].content)
	{
		i = 0;
		while (token[id].content[i])
		{
			gen->input[j] = token[id].content[i];
			i++;
			j++;
		}
		if (token[id + 1].content)
			gen->input[j++] = ' ';
		id++;
	}
	gen->input[j] = '\0';
}

void	make_it_string(t_data *gen, t_token *token)
{
	int	i;
	int	id;
	int	count;

	id = 0;
	count = 0;
	while (token[id].content)
	{
		i = 0;
		while (token[id].content[i])
		{
			count++;
			i++;
		}
		count++;
		id++;
	}
	free(gen->input);
	gen->input = (char *)ft_calloc(sizeof(char), count + 1);
	if (!gen->input)
	{
		ft_error("alloc error", 2, gen, "");
		return ;
	}
	fill_input(gen, token);
}

t_token	*reallocation_and_all(t_data *gen, t_token *token)
{
	make_it_string(gen, token);
	gen->token_num = num_token(gen->input, gen);
	if (gen->token_num == 0)
		return (NULL);
	free_all(token, gen, true);
	token = (t_token *)ft_calloc(sizeof(t_token), gen->token_num + 1);
	if (!token)
		return (write(2, "bash: malloc error\n", 14), NULL);
	alloc_str_token(token, gen);
	token_struct_init(token, gen);
	fill_struct(token, gen);
	if_inside_quote(token, gen);
	expanding_variables(token, gen);
	remove_quotes_token(token);
	fix_gen_token_num(token, gen);
	return (token);
}

//return 2 per syntax error
int	intersection(t_token *token, t_data *gen)
{
	int	i;

	i = 0;
	fill_struct(token, gen);
	if_inside_quote(token, gen);
	i = expanding_variables(token, gen);
	if (i == 1)
		return (1);
	else if (i == 2)
		return (2);
	if (remove_quotes_token(token) == 1)
		return (2);
	fix_gen_token_num(token, gen);
	token_struct_init(token, gen);
	return (0);
}
