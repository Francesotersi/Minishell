/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:58:54 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/20 15:23:06 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_error(char *str, int exit_c, t_data *gen, char *token)
{
	int	i;

	i = 0;
	write(2, "bash:minishell: ", 17);
	while (i < (int)ft_strlen(str))
		write(2, &str[i++], 1);
	i = 0;
	write(2, " '", 2);
	while (i < (int)ft_strlen(token))
		write(2, &token[i++], 1);
	write(2, "'\n", 2);
	gen->exit_code = exit_c;
}

void	skip_single_quotes(char *str, int *i)
{
	(*i)++;
	while (str[(*i)] != '\0' && str[(*i)] != '\'')
		(*i)++;
	if (str[(*i)] == '\'')
		(*i)++;
}

int	heredoc_d_case(t_token *token, int *id)
{
	if (!ft_strncmp(token[(*id)].content, "<<", \
		ft_strlen(token[(*id)].content) + 1) \
		&& find_char(&token[(*id) + 1], '$') == 1)
	{
		(*id)++;
		return (1);
	}
	return (0);
}

void	if_inside_quote(t_token *token, t_data *gen)
{
	int	id;
	int	i;

	(void)gen;
	id = 0;
	while (token[id].content)
	{
		i = 0;
		while (token[id].content && token[id].content[i])
		{
			if (token[id].content[i] == '\"' || token[id].content[i] == '\'')
			{
				token[id].t_quote = 1;
				break ;
			}
			i++;
		}
		id++;
	}
}

// conta il numero di token nella stringa per poter allocare al struttura
int	num_token(char *str, t_data *gen)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		if (count_char_token(str, &i, &len, gen) == 1)
			return (0);
		if (operator_token(str, &i, &len, gen) == 1)
			return (0);
	}
	return (len);
}
