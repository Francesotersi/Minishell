/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>              +#+  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:38:38 by ftersill            #+#    #+#           */
/*   Updated: 2025/03/28 09:38:38 by ftersill           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	copy_operator_fill(t_token token, char *str, int *i, int *token_id)
// {
// 	int	token_roll;

// 	token_roll = 0;
// 	while ((str[*i] == '>' || str[*i] == '<' || str[*i] == '&' \
// 		|| str[*i] == '|' || str[*i] == '(' || str[*i] == ')') \
// 		&& str[*i] != '\0')
// 	{
// 		if ((str[*i] == '<' && str[*i + 1] == '<') || \ //	caso per <<, >>, ||, &&, 
// 			(str[*i] == '>' && str[*i + 1] == '>') || \
// 			(str[*i] == '&' && str[*i + 1] == '&') || \
// 			(str[*i] == '|' && str[*i + 1] == '|'))
// 		{

// 		}
// 		else //  caso <, >

// 	}
// }

// va in segfault
void	copy_char_fill(t_token token, char *str, int *i, int *token_id)
{
	int token_roll;

	token_roll = 0;
	while (str[*i] != '\"' && str[*i] != '\'' && str[*i] != '&' \
		&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>' \
		&& str[*i] != ' ' && str[*i] != '(' && str[*i] != ')' \
		&& str[*i] != '\0')
	{
		token.str[token_roll] = str[*i];
		(*i)++;
		token_roll++;
		if (str[*i] != '\"' && str[*i] != '\'' && str[*i] != '&' \
				&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>' \
				&& str[*i] != ' ' && str[*i] != '(' && str[*i] != ')' \
				&& str[*i] != '\0')
			(*token_id)++;
	}
	printf("caccaa %s", token.str);
	// 					FORSE
	//aggiungere qua la parte per contare gli spazi a sinistra del token
}

void	fill_struct(t_token *token, t_data *gen)
{
	int	token_id;
	int i;

	i = 0;
	token_id = 0;
	while (gen->input[i] == ' ' && gen->input[i] != '\0')
		i++;
	while (gen->input[i] != '\0')
	{
		copy_char_fill(token[token_id], gen->input, &i, &token_id);
		// copy_operator_fill(token[token_id], gen->input, &i, &token_id);
		
	}
	printf_struct(token, gen);
}
