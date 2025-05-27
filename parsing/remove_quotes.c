/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:48:07 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/27 15:57:20 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fix_gen_token_num(t_token *token, t_data *gen)
{
	int	i;

	i = 0;
	while (token[i].content != NULL)
	{
		i++;
	}
	gen->token_num = i;
}

char	*actual_removal_temp_alloc(t_token *token)
{
	char	*temp;

	temp = ft_strdup(token->content);
	free(token->content);
	token->content = (char *)ft_calloc(ft_strlen(temp) + 1, sizeof(char));
	if (!token->content)
	{
		free_all(token, NULL, false);
		return (NULL);
	}
	return (temp);
}

int	check_before_escape(t_token *token, int *j, char *temp, int *i)
{
	if (temp[(*i)] && temp[(*i)] == '\\')
	{
		if (temp[++(*i)] && (temp[(*i)] == '\"' || \
			temp[(*i)] == '\''))
			token->content[(*j)++] = temp[(*i)];
		return (1);
	}
	return (0);
}

int	actual_removal(t_token *token, char *temp)
{
	int		j;
	char	quote;
	int		i;

	i = 0;
	j = 0;
	while (temp[i] != '\0')
	{
		quote = temp[i];
		if (check_before_escape(token, &j, temp, &i) == 1)
			continue ;
		if (quote == '\"' || quote == '\'')
		{
			i++;
			while (temp[i] != '\0' && temp[i] != quote)
				if (actual_removal_2(token, temp, &i, &j) == 1)
					break ;
			i++;
			continue ;
		}
		token->content[j++] = temp[i++];
	}
	free(temp);
	return (0);
}

// funzione chiamata nel file fill_struct.c in fondo 
// all`ultima funzione del file
int	remove_quotes_token(t_token *token)
{
	int		id;
	int		i;
	char	*temp;

	i = 0;
	id = 0;
	temp = NULL;
	while (token[id].content != NULL)
	{
		while (token[id].content[i] != '\0')
		{
			if ((token[id].content[i] == '\'' || token[id].content[i] == '\"' ))
			{
				temp = actual_removal_temp_alloc(&token[id]);
				if (actual_removal(&token[id], temp) == 1)
					return (free(temp), 1);
				break ;
			}
			i++;
		}
		i = 0;
		id++;
	}
	return (0);
}
