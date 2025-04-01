/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:13:21 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/01 12:43:58 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Cut a string from start to end (included).

Example:
string = "Hello world!"
start = 5
end = 5
string becomes: "Helloworld!\0"
*/
// int	cut_string(char *string, size_t start, size_t end)
// {
// unsigned int	temp;
// unsigned int	temp1;
// unsigned int	string_len;
// end++;
// if (!(string) || !(*string) || (start > end))
// 	return (1);
// 	string_len = 0;
// 	while (string[string_len])
// 		++string_len;
// 	temp = start;
// 	while ((start != end) && (string[start] != 0))
// 		string[start++] = 0;
// 	end = start;
// 	start = temp;
// 	temp = 0;
// 	temp1 = string_len;
// 	while (end != string_len--)
// 	{
// 		string[start + temp] = string[end + temp];
// 		++temp;
// 	}
// 	string[temp1 - (end - start)] = 0;
// 	return (0);
// }

void	printf_struct(t_token *token, t_data *gen)
{
	int	i;

	i = 0;
	(void)token;
	while (i < gen->token_num)
	{
		printf("stringa contenuta nel token %d == %s\n",i , token[i].str);
		i++;
	}
}

// fa il free del contenuto dei token
void	free_token(t_token *token, t_data *gen)
{
	int	i;

	i = 0;
	while (i < gen->token_num)
	{
		free(token[i].str);
		i++;
	}
}

// funzione che fa free sullo struct
void	free_struct(t_token *token)
{
	free(token);
}

// fa il free di tutto
void	free_all(t_token *token, t_data *gen)
{
	free_token(token, gen);
	free_struct(token);
}
