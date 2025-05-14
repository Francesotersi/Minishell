/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:47:11 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/14 12:52:38 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	even_more_cases(t_token *tok, int *id, t_data *gen)
{
	if (!ft_strncmp(tok[(*id)].content, ")", ft_strlen(tok[(*id)].content))
		&& tok[(*id) + 1].content)
	{
		if (tok[(*id) + 1].type != AND && tok[(*id) + 1].type != OR \
			&& tok[(*id) + 1].content[0] != ')' && \
			tok[(*id) + 1].type != PIPE)
			return (ft_error("syntax error near unexpected token 3", 2, \
				gen, tok[(*id) + 1].content), 1);
	}
	if ((tok[(*id)].type == RED_IN || tok[(*id)].type == RED_O_APPEND || \
		tok[(*id)].type == RED_OUT || tok[(*id)].type == HERE_DOC) && \
		tok[(*id) + 1].content)
	{
		if (!ft_strncmp(tok[(*id) + 1].content, "<", \
			ft_strlen(tok[(*id) + 1].content)) || \
			!ft_strncmp(tok[(*id) + 1].content, ">", ft_strlen(\
			tok[(*id) + 1].content)) || !ft_strncmp(tok[(*id) + 1].content, \
			"<<", ft_strlen(tok[(*id) + 1].content) || \
			!ft_strncmp(tok[(*id) + 1].content, ">>", \
			ft_strlen(tok[(*id) + 1].content))))
			return (ft_error("syntax error near unexpected token 15", 2,
					gen, tok[(*id) + 1].content), 1);
	}
	return (0);
}
