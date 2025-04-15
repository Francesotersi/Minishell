/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:51:32 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/15 13:50:34 by ftersill         ###   ########.fr       */
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
//	4) dare syntax error quando le parentesi non sono chiuse e quando prima di una parentesi non e` presente un operatore
//  5) i token dopo qualsiasi redirection sono nomi di file 
//	6) il primo token e` sempre un comando
//



//	conta il numero di parentesi nell`input dello user perche 
//	se il numero delle parentesi aperte non e` uguale a quello delle 
//	parentesi chiuse deve dare syntax error

int	count_parenthesis(t_token *token, t_data *gen)
{
	int	id;
	int	open_par_count;
	int close_par_count;

	(void)gen;
	open_par_count = 0;
	close_par_count = 0;
	id = 0;
	while (token[id].content != NULL)
	{
		if (ft_strcmp(token[id].content, ")") == 0)
			close_par_count++;
		else if (ft_strcmp(token[id].content, "(") == 0)
			open_par_count++;
		id++;
	}
	if (close_par_count != open_par_count)
		return (1);
	return (0);
}

//	assegna la priorita` ad ogni singolo token in base alle parentesi tonde
int	prior_of_token(t_token *token, t_data *gen, int prior, int token_id)
{
	int	id;

	id = token_id;
	while (token[id].content != NULL)
	{
		if (ft_strcmp(token[id].content, "(") == 0)
		{
			token[id].prior = prior + 1;
			id++;
			prior_of_token(token, gen, prior + 1, id);
		}
		else if (ft_strcmp(token[id].content, ")") == 0)
		{																// non funziona
			token[id].prior = prior - 1;
			id++;
			prior_of_token(token, gen, prior - 1, id);
		}	
		else
		{
			id++;
			token[id].prior = prior;
		}
	}
	return(0);
}

int	define_token_arg(t_token *token, t_data *gen)
{
	int	i;
	int	id;

	i = 0;
	id = 0;
	while (token[id].content != NULL)
	{
		if (count_parenthesis(token, gen))
			return (printf("MRASDSADASDAD\n"), 1);
		if (prior_of_token(token, gen, 0, 0))
			return (1);
		id++;
	}
	return (0);
}
