/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>              +#+  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:51:32 by ftersill            #+#    #+#           */
/*   Updated: 2025/04/04 16:51:32 by ftersill           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//			TO DEFINE IN TOKEN STRUCT
//	1) tipo di token
// 
//	3) priorita rispetto alle parentesi (piu altro e` il numero maggiore e` la priorita`)
//

int

int	define_token_arg(t_token *token, t_data *gen)
{
	int	i;
	int	token_id;

	i = 0;
	token_id = 0;
	while (token_id < gen->token_num)
	{
		if (type_of_token(token, gen) == 1)
			return (1);
	}
}
