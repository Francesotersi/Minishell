/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_lexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:05:20 by ftersill          #+#    #+#             */
/*   Updated: 2025/03/27 12:02:58 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	operator_token(char *str, int *i, int *len)
{
	while ((str[*i] == '>' || str[*i] == '<' || str[*i] == '&' \
		|| str[*i] == '|' || str[*i] == '(' || str[*i] == ')') \
		&& str[*i] != '\0')
	{
		if ((str[*i] == '<' && str[*i + 1] == '>') || \
				(str[*i] == '>' && str[*i + 1] == '<') || \
				(str[*i] == '&' && str[*i + 1] != '&') || \
				(str[*i] == '|' && str[*i + 1] == '|' && str[*i + 2] == '|'))
			return (1);
		else if ((str[*i] == '<' && str[*i + 1] == '<') || \
				(str[*i] == '>' && str[*i + 1] == '>') || \
				(str[*i] == '&' && str[*i + 1] == '&') || \
				(str[*i] == '|' && str[*i + 1] == '|'))
		{
			(*i)++;
			(*len)++;
		}
		else
			(*len)++;
		(*i)++;
	}
	return (0);
}

// gestisce le quotes
int	quotes_token(char *str, int *i, int *len)
{
	if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] != '\"' && str[*i] != '\0')
			(*i)++;
		if (str[*i] == '\0')
			return (1);
		(*i)++;
		(*len)++;
	}
	else if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'' && str[*i] != '\0')
			(*i)++;
		if (str[*i] == '\0')
			return (1);
		(*i)++;
		(*len)++;
	}
	return (0);
}

void	count_char_token(char *str, int *i, int *len)
{
	int temp;

	temp = 0;
	while (str[*i] != '\"' && str[*i] != '\'' && str[*i] != '&' \
		&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>' \
		&& str[*i] != ' ' && str[*i] != '(' && str[*i] != ')' \
		&& str[*i] != '\0')
	{
		if (temp == 0 && str[*i])
		{
			(*len)++;
			temp = 1;
		}
		(*i)++;
	}
}

// conta il numero di token nella stringa per poter allocare al struttura
int	num_token(char *str)
{
	int	i;
	int	temp;
	int	len;

	i = 0;
	temp = 0;
	len = 0;
	while (str[i] != '\0')
	{ 
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		count_char_token(str, &i, &len);
		if (operator_token(str, &i, &len) == 1)
			return (write(2, "bash: syntax error\n", 20), 0);
		if (quotes_token(str, &i, &len) != 0)
			return (write(2, "bash: syntax error\n", 20), 0);
	}
	return (len + 1);
}
//		to-do list:
//	X) Allocare la stringa
//	2) riempire la struttura con le stringhe
//  3) fare controlli per il parsing effettivo
//
//		casi limite
//	1) cat <(ls) = funziona solo se le parentesi sono attaccate
//	
int	start_lexing(t_data *gen)
{
	t_token			*token;
	int				struct_len;

	struct_len = num_token(gen->input);
	if (struct_len == 0)
		return (1);
	printf("len = %d\n", struct_len);
	token = (t_token*)malloc(sizeof(t_token) * struct_len);
	if (!token)
		return (write(2, "malloc error\n", 14), 1);
	// fill_struct_token(token)
	return (0);
}
