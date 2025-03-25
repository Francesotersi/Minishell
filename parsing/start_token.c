/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:05:20 by ftersill          #+#    #+#             */
/*   Updated: 2025/03/25 12:58:35 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*	1)controllare che la stringa passata non sia aperta
	2)calcolare la grandezza della struttura
		attento alla divisione con le redirection
*/

// gestisce le redirection
void	redirect_token(char *str, int *i, int *len)
{
	if (str[*i] == '>' || str[*i] == '<')
	{
		if (str[*i - 1] != ' ')
		{
			
		}
	}
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
		if (str[++(*i)] != ' ' && str[(*i)] != '\0')
			(*len)++;
		(*len)++;
	}
	else if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'' && str[*i] != '\0')
			(*i)++;
		if (str[*i] == '\0')
			return (1);
		if (str[++(*i)] != ' ' && str[(*i)] != '\0')
			(*len)++;
		len++;
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
		// redirect_token(str, &i, &len,);
		if (quotes_token(str, &i, &len) != 0)
			return (write(2, "bash: syntax error\n", 20), 0);
		else if (str[i] != '\0' && str[i] != ' ' && temp == 0)
		{
			len++;
			temp = 1;
		}
		else if (str[i] != '\0' && str[i] == ' ')
			temp = 0;
		i++;
	}
	return (len + 1);
}

int	start_lexing(t_data *gen)
{
	struct t_token	*token;
	int				struct_len;

	struct_len = num_token(gen->input);
	if (struct_len == 0)
		return (1);
	printf("%d\n", struct_len);
	// token = (t_token)malloc();
	// if (!token)
	// 	return (perror("malloc error"), 1);
	return (0);
}
