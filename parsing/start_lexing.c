/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_lexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:05:20 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/01 12:33:38 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// se && o || = token singoli
// se redirection = token singoli
// per il resto mettere tutto dentro un token singolo con delimitatore ' '

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
int	quotes_token(char *str, int *i, int *len, int *temp)
{
	if (str[*i] == '\"')
	{
		while (str[++(*i)] != '\"' && str[*i] != '\0');
		if (str[*i] == '\0')
			return (1);
		if ((*temp) == 0 && str[*i])
		{
			(*len)++;
			(*temp) = 1;
		}
		quotes_token(str, i, len, temp);
	}
	if (str[*i] == '\'')
	{
		while (str[++(*i)] != '\'' && str[*i] != '\0');
		if (str[(*i)++] == '\0')
			return (1);
		if ((*temp) == 0 && str[*i])
		{
			(*len)++;
			(*temp) = 1;
		}
		quotes_token(str, i, len, temp);
	}
	return (0);
}

int	count_char_token(char *str, int *i, int *len)
{
	int temp;

	temp = 0;
	while (str[*i] != '&' && str[*i] != '|' && str[*i] != '<' \
		&& str[*i] != '>' && str[*i] != ' ' && str[*i] != '(' \
		&& str[*i] != ')' && str[*i] != '\0')
	{
		if (temp == 0 && str[*i])
		{
			(*len)++;
			temp = 1;
		}
		if (quotes_token(str, i, len, &temp) == 1)
			return (1);
		(*i)++;
	}
	return (0);
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
		if (count_char_token(str, &i, &len) == 1)
			return (write(2, "bash: syntax error\n", 20), 0);
		if (operator_token(str, &i, &len) == 1)
			return (write(2, "bash: syntax error\n", 20), 0);
	}
	return (len);
}
//		to-do list:
//	X) Allocare la stringa
//	2) riempire la struttura con le stringhe
//  3) fare controlli per il parsing effettivo
//
//		casi limite
//	1) cat <(ls) = funziona solo se le parentesi sono attaccate
//
// 		RICORDA!
// 	1) La struttura e le stringhe all`interno di essa devono essere freeate
//	
int	start_lexing(t_data *gen)
{
	t_token			*token;
	
	gen->token_num = 0;
	gen->token_num = num_token(gen->input);
	if (gen->token_num == 0)
		return (1);
	// printf("len = %d\n", gen->token_num);
	token = (t_token*)malloc(sizeof(t_token) * gen->token_num);
	if (!token)
		return (write(2, "bash: malloc error\n", 14), 1);
	(*token) = (t_token){0};
	if (alloc_str_token(token, gen) == 1)
		return (1);
	fill_struct(token, gen);

	// free_all(token, gen);

	return (0);
}
