/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:53:39 by ftersill          #+#    #+#             */
/*   Updated: 2025/03/19 14:58:03 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// readline ritorna una stringa da freeare ad ogni input
int	start(t_data *gen)
{
	while (1)
	{
		gen->input = readline("minishell$> ");
		if (!gen->input)
			return(0);
		//if (start_parsing(gen) == 1)
		//	return (0);
		free(gen->input);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data gen;

	(void)ac, (void)env, (void)av;
	gen = (t_data){0};
	gen.env = env;
	if (start(&gen) == 1)
		return (1);
	return (0);
}
