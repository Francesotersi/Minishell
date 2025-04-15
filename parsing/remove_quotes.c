/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:48:07 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/15 09:37:25 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fix_gen_token_num(t_token *token, t_data *gen)
{
	int	i;

	i = 0;
	while (token[i].str != NULL)
	{
		i++;
	}
	gen->token_num = i;
}

char *actual_removal_temp_alloc(t_token *token)
{
	char *temp;

	temp = ft_strdup(token->str);
	free(token->str);
	token->str = (char*)ft_calloc(ft_strlen(temp) - 2 + 1, sizeof(char));
	if (!token->str)
	{
		free_all(token, NULL);
		return (NULL);
	}
	return (temp);
}

void	actual_removal(t_token *token, bool check, char *temp)
{
	int		j;
	char	quote;
	int		i;

	(void)check;
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
				token->str[j++] = temp[i++];
			}
			i++;
			continue ;
		}
		token->str[j++] = temp[i++];
	}
	free(temp);
}

void	remove_quotes_token(t_token *token, t_data *gen)
{
	int		id;
	int		i;
	bool	check;
	char	*temp;

	check = false;
	i = 0;
	id = 0;
	temp = NULL;
	while (token[id].str != NULL)
	{
		while(token[id].str[i] != '\0')
		{
			if (token[id].str[i] == '\'' || token[id].str[i] == '\"')
			{
				temp = actual_removal_temp_alloc(&token[id]);
				actual_removal(&token[id], check, temp);
				break ;
			}
			i++;
		}
		i = 0;
		id++;
	}
	fix_gen_token_num(token, gen);
}
