/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:00:35 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/21 12:44:42 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	convert_wildcard(char *old_str, char **new_str);

int	find_char(t_token *token, char c)
{
	int	i;

	i = 0;
	while (token->content && token->content[i])
	{
		if (token->content[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	wildcard_d_case(t_token *token, t_data *gen, int *id)
{
	(void)gen;
	if (!ft_strncmp(token[(*id)].content, "<<", ft_strlen(token[(*id)].content)
		) && find_char(&token[(*id) + 1], '*') == 1)
	{
		(*id) += 2;
		return (1);
	}
	return (0);
}

int	expand_wildcard(t_token *token, t_data *gen)
{
	int		id;
	char	*temp;
	int		if_expanded;

	id = 0;
	temp = NULL;
	if_expanded = 0;
	while (token[id].content)
	{
		if (wildcard_d_case(token, gen, &id) == 1)
			continue ;
		if (find_char(&token[id], '*') == 1)
		{
			temp = ft_strdup(token[id].content);
			if (convert_wildcard(temp, &token[id].content) == 1)
			{
				free(temp);
				return (ft_error("alloc error", 2, gen, ""), 1);
			}
			if_expanded = 1;
			free(temp);
		}
		id++;
	}
	return (if_expanded);
}
