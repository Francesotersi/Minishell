/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:51:32 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/15 09:44:32 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h" 

// types:

// COMMAND = 0;
// ARGUMENT = 1;
// FILE = 2;
// > = 3;
// < = 4;
// >> = 5;
// << = 6;
// | = 7;
// && = 8;
// || = 9; 
// * = 10.

//			TO DEFINE IN TOKEN STRUCT
//	1) tipo di token
//
//	3) priorita rispetto alle parentesi (piu alto e` il numero, maggiore e` la priorita`)
//	4) dare syntax error quando le parentesi non sono chiuse
//  5) i token dopo qualsiasi redirection sono nomi di file 
//	6) il primo token e` sempre un comando
//

int	type_of_token(t_token *token, t_data *gen)
{
	int	token_id;

	token_id = 0;
	while (token_id[token_id] < gen->token_num)
	{
		
		
	}
}

int	define_token_arg(t_token *token, t_data *gen)
{
	int	i;
	int	token_id;

	i = 0;
	token_id = 0;
	// while (token_id < gen->token_num)
	// {
		if (type_of_token(token, gen) == 1)
			return (1);
		if (prior_of_token(token, gen))
	// }
}
