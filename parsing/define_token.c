/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:51:32 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/30 08:51:10 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h" 

// types:

// COMMAND = 0,
// ARGUMENT = 1,
// FILES = 2,
// RED_OUT = 3,
// RED_IN = 4,
// RED_O_APPEND = 5,
// HERE_DOC = 6,
// PIPE = 7,
// AND = 8,
// OR = 9,
// WILDCARD = 10,

//			TO DEFINE IN TOKEN STRUCT
//	1) tipo di token
//	4) dare syntax error quando prima di una parentesi non e` presente un operatore
//  5) i token dopo qualsiasi redirection sono nomi di file 
//	6) il primo token e` sempre un comando
//





int	define_token_and_parenthesis(t_token *token, t_data *gen)
{
	int	i;
	int	id;

	i = 0;
	id = 0;
	while (token[id].content != NULL)
	{
		if (count_parenthesis(token, gen))
			return (/* syntax error */ 1);
		if (prior_of_token(token, gen))
			return (1);
		id++;
	}
	define_token_arg(token, gen);
	return (0);
}
