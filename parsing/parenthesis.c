/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:30:09 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/08 11:11:43 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// FUNZIONI CHIAMATE ALLA FINE DEL FILE EXPAND_ENV.C 
//	conta il numero di parentesi nell`input dello user perche 
//	se il numero delle parentesi aperte non e` uguale a quello delle 
//	parentesi chiuse deve dare syntax error
int	count_parenthesis(t_token *token, t_data *gen)
{
	int	id;
	int	open_par_count;
	int	close_par_count;

	(void)gen;
	open_par_count = 0;
	close_par_count = 0;
	id = 0;
	while (token[id].content != NULL)
	{
		if (ft_strncmp(token[id].content, ")", 1) == 0)
			close_par_count++;
		else if (ft_strncmp(token[id].content, "(", 1) == 0)
			open_par_count++;
		id++;
	}
	if (close_par_count != open_par_count)
		return (1);
	return (0);
}

//	assegna la priorita` ad ogni singolo token in base alle parentesi tonde
int	prior_of_token(t_token *token, t_data *gen)
{
	int	id;
	int	prior;

	(void)gen;
	id = 0;
	prior = 0;
	while (token[id].content != NULL)
	{
		if (ft_strncmp(token[id].content, "(", 1) == 0)
			prior++;
		if (ft_strncmp(token[id].content, ")", 1) == 0)
			prior--;
		token[id].prior = prior;
		id++;
	}
	return (0);
}
