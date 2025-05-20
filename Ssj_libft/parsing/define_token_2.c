/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:04:29 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/14 12:39:57 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_redirection_2(t_token *tok, int *id)
{
	tok->type = RED_IN;
	if (tok->content && \
	!ft_strncmp((tok + 1)->content, "(", ft_strlen(tok->content)))
	{
		(tok + 1)->type = PARENTHESIS;
		(*id) += 1;
		return (1);
	}
	return (0);
}

int	is_redirection_3(t_token *tok, t_data *gen, int *id)
{
	(void)gen, (void)id;
	if ((tok + 1)->content)
	{
		if (!ft_strncmp((tok + 1)->content, "<", \
			ft_strlen((tok + 1)->content)) && !ft_strncmp((tok + 1)->content, \
			">", ft_strlen((tok + 1)->content)) \
			&& !ft_strncmp((tok + 1)->content, "<<", \
			ft_strlen((tok + 1)->content)) && ft_strncmp((tok + 1)->content, \
			">>", ft_strlen((tok + 1)->content)))
			return (1);
	}
	return (0);
}

int	is_redirection(t_token *tok, t_data *gen, int *id)
{
	(void)gen;
	if (is_redirection_3(tok, gen, id) == 1)
		return (1);
	if (!ft_strncmp(tok->content, ">", ft_strlen(tok->content)))
		tok->type = RED_OUT;
	else if (!ft_strncmp(tok->content, "<", ft_strlen(tok->content)))
	{
		if (is_redirection_2(tok, id) == 1)
			return (0);
	}
	else if (!ft_strncmp(tok->content, "<<", ft_strlen(tok->content)))
		tok->type = HERE_DOC;
	else if (!ft_strncmp(tok->content, ">>", ft_strlen(tok->content)))
		tok->type = RED_O_APPEND;
	if (!ft_strncmp((tok + 1)->content, "(", ft_strlen(tok->content)))
		return (1);
	if (!ft_strncmp((tok + 1)->content, ")", ft_strlen(tok->content)))
		(*id)++;
	else if ((tok + 1)->content)
		(tok + 1)->type = FILES;
	(*id) += 1;
	return (0);
}

int	is_cmd_2(t_token *tok, int *id)
{
	if ((*id) >= 2)
	{
		if (tok[(*id)].type == ARGUMENT && \
			tok[(*id) - 1].type == PARENTHESIS && \
			tok[(*id) - 2].type == RED_IN)
			return (1);
	}
	return (0);
}

int	is_cmd(t_token *tok, t_data *gen)
{
	int	id;

	id = 0;
	(void)gen;
	while (tok[id].content != NULL)
	{
		while (tok[id].content && tok[id].type != ARGUMENT)
			id++;
		if (is_cmd_2(tok, &id) == 1)
			tok[id].type = COMMAND;
		else if (tok[id].type == ARGUMENT)
			tok[id].type = COMMAND;
		while (tok[id].content && tok[id].type != AND && tok[id].type != OR
			&& tok[id].type != PIPE)
		{
			if (is_cmd_2(tok, &id) == 1)
				break ;
			id++;
		}
	}
	return (0);
}
