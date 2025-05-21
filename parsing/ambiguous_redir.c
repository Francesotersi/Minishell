/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:31:35 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/21 13:01:41 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ambiguous_var(t_token *token, t_data *gen)
{
	char	*temp;
	int		i;
	char	*search;

	temp = NULL;
	search = NULL;
	i = 0;
	if (token->content[i])
	{
		temp = what_to_search(token, &i);
		search = get_env(gen->env, temp);
		if (!search || !ft_strncmp(search, "", ft_strlen(search)))
		{
			ft_error("ambiguous redirection", 1, gen, "");
			return (free(temp), 1);
		}
	}
	free(temp);
	return (0);
}

int	ambiguous_redir(t_token *token, t_data *gen)
{
	int	id;

	id = -1;
	while (token && token[++id].content)
	{
		if ((!ft_strncmp(token[id].content, ">", ft_strlen(token[id].content) \
	) || !ft_strncmp(token[id].content, ">>", ft_strlen(token[id].content)) || \
		!ft_strncmp(token[id].content, "<", ft_strlen(token[id].content))) && \
	token[id + 1].content)
		{
			if (token[id + 1].content[0] && token[id + 1].content[0] == '$' && \
				token[id + 1].content[1] && !(token[id + 1].content[1] == '?'))
			{
				if (token[id + 1].content[1])
					if (ambiguous_var(&token[id + 1], gen) == 1)
						return (1);
			}
			if (token[id + 1].content[0] && token[id + 1].content[0] == '*' && \
				!token[id + 1].content[1])
				return (ft_error("ambiguous redirection", 1, gen, ""), 1);
		}
	}
	return (0);
}
