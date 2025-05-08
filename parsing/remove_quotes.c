/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:48:07 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/08 10:07:07 by ftersill         ###   ########.fr       */
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
	token->content = (char *)ft_calloc(ft_strlen(temp) - 2 + 1, sizeof(char));
	if (!token->content)
	{
		free_all(token, NULL);
		return (NULL);
	}
	return (temp);
}

void	actual_removal(t_token *token, char *temp)
{
	int		j;
	char	quote;
	int		i;

	i = 0;
	j = 0;
	while (temp[i] != '\0')
	{
		quote = temp[i];
		if (quote == '\"' || quote == '\'')
		{
			i++;
			while (temp[i] != '\0' && temp[i] != quote)
			{
				token->content[j++] = temp[i++];
			}
			i++;
			continue ;
		}
		token->content[j++] = temp[i++];
	}
	free(temp);
}

// funzione chiamata nel file fill_struct.c in fondo 
// all`ultima funzione del file
void	remove_quotes_token(t_token *token, t_data *gen)
{
	int		id;
	int		i;
	char	*temp;

	i = 0;
	id = 0;
	temp = NULL;
	expanding_variables(token, gen);
	while (token[id].content != NULL)
	{
		while (token[id].content[i] != '\0')
		{
			if (token[id].content[i] == '\'' || token[id].content[i] == '\"')
			{
				temp = actual_removal_temp_alloc(&token[id]);
				actual_removal(&token[id], temp);
				break ;
			}
			i++;
		}
		i = 0;
		id++;
	}
	fix_gen_token_num(token, gen);
}
