/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:47:11 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/21 11:40:40 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	redir_subshell_case(t_token *tok, int *id, t_data *gen)
{
	int	i;
	int	layer;

	(void)gen;
	i = (*id) - 1;
	layer = tok[(*id)].prior;
	while (i >= 0 && layer != tok[(*id)].prior + 1 && \
		ft_strncmp(tok[i].content, "(", ft_strlen(tok[i].content)))
		i--;
	if (i < 0 || ft_strncmp(tok[i].content, "(", ft_strlen(tok[i].content)))
		return (1);
	if (i == 0)
		return (0);
	if (tok[i - 1].type != AND && tok[i - 1].type != OR \
		&& tok[i - 1].content[0] != '(' && \
		tok[i - 1].type != PIPE && tok[i - 1].type != RED_IN)
		return (1);
	return (0);
}

int	even_even_more_cases(t_token *tok, int *id, t_data *gen)
{
	if (!ft_strncmp(tok[(*id)].content, ")", ft_strlen(tok[(*id)].content))
		&& tok[(*id) + 1].content)
	{
		if (tok[(*id) + 1].type != AND && tok[(*id) + 1].type != OR \
			&& tok[(*id) + 1].content[0] != ')' && \
			tok[(*id) + 2].type != PIPE)
			if (redir_subshell_case(tok, id, gen) == 1)
				return (ft_error("syntax error near unexpected token 3", 2, \
					gen, tok[(*id) + 4].content), 1);
	}
	if (tok[(*id)].type == PIPE && tok[(*id) + 1].content && \
	is_exec_sep(tok[(*id) + 1].type))
		return (ft_error("syntax error near unexpected token 30", 2, \
			gen, tok[(*id) + 1].content), 1);
	return (0);
}

int	even_more_cases(t_token *tok, int *id, t_data *gen)
{
	if (even_even_more_cases(tok, id, gen) == 1)
		return (1);
	if ((tok[(*id)].type == RED_IN || tok[(*id)].type == RED_O_APPEND || \
		tok[(*id)].type == RED_OUT || tok[(*id)].type == HERE_DOC) && \
		tok[(*id) + 1].content)
	{
		if ((!ft_strncmp(tok[(*id) + 1].content, "<", \
			ft_strlen(tok[(*id) + 1].content)) || \
			!ft_strncmp(tok[(*id) + 1].content, ">", ft_strlen(\
			tok[(*id) + 1].content)) || !ft_strncmp(tok[(*id) + 1].content, \
			"<<", ft_strlen(tok[(*id) + 1].content)) || \
			!ft_strncmp(tok[(*id) + 1].content, ">>", \
			ft_strlen(tok[(*id) + 1].content))) && tok[(*id) + 1].content)
			return (ft_error("syntax error near unexpected token 15", 2,
					gen, tok[(*id) + 1].content), 1);
	}
	if ((tok[(*id)].type == RED_IN || tok[(*id)].type == RED_O_APPEND || \
		tok[(*id)].type == RED_OUT || tok[(*id)].type == HERE_DOC) && \
		!tok[(*id) + 1].content)
		return (ft_error("syntax error near unexpected token 30", 2, \
			gen, tok[(*id)].content), 1);
	return (0);
}
