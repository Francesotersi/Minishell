/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cmd_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:45:17 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/27 10:54:23 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	find_something(char *s, char searched, int *i, char *t_quote)
{
	char	invalid_quotes;

	invalid_quotes = 0;
	while (s[*i])
	{
		if (*t_quote == s[*i])
			*t_quote = 0;
		else if ((!*t_quote) && (s[*i] == '\'' || s[*i] == '\"'))
			*t_quote = s[*i];
		else if (!*t_quote && s[*i] == searched)
			break ;
		else if (searched != '$')
			return (-1);
		if (searched != '$' && *t_quote)
			invalid_quotes = 1;
		++(*i);
	}
	if (!s[*i])
		return (-1);
	else if (invalid_quotes)
		return (-2);
	return (*i);
}

int	parse_prompt(char *s, int *i, char *t_quote, t_data *gen)
{
	int		dollar_i;
	int		frst_p_i;

	dollar_i = find_something(s, '$', i, t_quote);
	if (dollar_i == -1)
		return (-1);
	++(*i);
	frst_p_i = find_something(s, '(', i, t_quote);
	if (frst_p_i == -1)
	{
		return (-1);
	}
	else if (frst_p_i == -2)
	{
		return (ft_error("syntax error near quote", 2, gen, ""), -2);
	}
	return (dollar_i);
}
