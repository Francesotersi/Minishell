/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:48:07 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/09 15:27:29 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"



void	actual_removal(t_token *token)
{
	char	quote;
	char	*temp;
	int		i;
	int		roll;
	tekken 3 online
	i = 0;
	roll = 0;
	temp = ft_strdup(token->str);
	free(token->str);
	token->str = (char*)ft_calloc(ft_strlen(temp) - 2 + 1, sizeof(char));
	if (!token->str)
		return (free_all(token, NULL));
	while (temp[i])
	{
		if (temp[i] == '\'' || temp[i] == '\"')
		{
			quote = temp[i++];
			while (temp[i] && temp[i] != quote)
				token->str[roll++] = temp[i++];
			if (temp[i] != quote)
				i++;
			continue ;
		}
		token->str[roll++] = temp[i];
		i++;
	}
}

void	remove_quotes_token(t_token *token)
{
	int	id;
	int	i;

	i = 0;
	id = 0;
	while (token[id].str)
	{
		while (token[id].str[i])
		{
			if (token[id].str[i] == '\"' || token[id].str[i] == '\'')
			{
				actual_removal(&token[id]);
				break ;
			}
			else
				i++;
		}
		i = 0;
		id++;
	}
}