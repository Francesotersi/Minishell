/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_lexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:05:20 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/05 15:32:11 by ftersill         ###   ########.fr       */
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
int	quotes_token(char *str, int *i, int *len, int *temp)
{
	(void)temp;
	if (str[(*i)] == '\"' && str[(*i)] != '\0')
	{
		(*len)++;
		while (str[++(*i)] != '\"' && str[(*i)] != '\0');
		if (str[(*i)] == '\0')
			return (2);
		if (str[(*i)] == '\"')
			(*i)++;
		return (1);
	}
	if (str[(*i)] == '\'' && str[(*i)] != '\0')
	{
			(*len)++;
		while (str[++(*i)] != '\'' && str[(*i)] != '\0');
		if (str[(*i)] == '\0')
			return (2);
		if (str[(*i)] == '\'')
			(*i)++;
		return (1);
	}
	return (0);
}

int	count_char_token(char *str, int *i, int *len)
{
	int temp;
	int	temp2;

	temp = 0;
	temp2 = 0;
	while (str[*i] != '&' && str[*i] != '|' && str[*i] != '<' \
	&& str[*i] != '>' && str[*i] != ' ' && str[*i] != '(' \
	&& str[*i] != ')' && str[*i] != '\0')
	{
		temp2 = quotes_token(str, i, len, &temp);
		if (temp2 == 2)
			return (1);
		else if (temp2 == 1)
			continue ;
		else if (temp == 0 && str[*i])
		{
			(*len)++;
			temp = 1;
		}
		if (str[*i])
			(*i)++;
	}
	return (0);
}

// conta il numero di token nella stringa per poter allocare al struttura
int	num_token(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{ 
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		// aggiungere token per il dollaro
		if (count_char_token(str, &i, &len) == 1)
			return (write(2, "bash: syntax error\n", 20), 0);
		if (operator_token(str, &i, &len) == 1)
			return (write(2, "bash: syntax error\n", 20), 0);
	}
	return (len);
}

//		to-do list:
//	X) Allocare la stringa
//	X) riempire la struttura con le stringhe
//  3) fare controlli per il parsing effettivo
//
//		casi limite
//
// 		RICORDA!
// 	1) La struttura e le stringhe all`interno di essa devono essere freeate
// 	2) QUANDO VAI AD ESPANDERE RICORDATI DI INSERIRE DELLE "" DOPO IL PRIMO SPAZIO COSI` ALMENO ALLA FINE DI TUTTO LE RIMUOVI
//	2) DEVI CAMBIARE L`ORDINE IN CUI FAI LE COSE NEL PROGRAMMA PERCHE BISOGNA ANCORA IMPLEMENTARE LE ESPANSIONI INFINITE E ALTRA ROBA
//	   ES. DIVIDI IN TOKEN-->ESPANSIONE EXIT CODE-->ESPANSIONE-->-->RIMUOVI QUOTES
// 				 ^         	                             |
//               \--------------------------------------/  

int	start_lexing(t_data *gen)
{
	t_token			*token;

	gen->token_num = num_token(gen->input);
	if (gen->token_num == 0)
		return (1);
	token = (t_token*)ft_calloc(sizeof(t_token),  gen->token_num + 1);
	if (!token)
		return (write(2, "bash: malloc error\n", 14), 1);
	token_struct_init(token, gen);
	(*token) = (t_token){0};
	if (alloc_str_token(token, gen) == 1)
		return (1);
	fill_struct(token, gen);
	// da fare define_token_arg e aggiungerlo al .h sta nel file define_token.h
	if (define_token_and_parenthesis(token, gen) == 1)
		return (1);
	gen->token = token;
	// printf_struct(token, gen);
	// free_all(token, gen);

	return (0);
}
