/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:53:39 by ftersill          #+#    #+#             */
/*   Updated: 2025/03/21 11:40:56 by ftersill         ###   ########.fr       */
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
			return(write(1, "exit\n", 5), 0);
		if (gen->input[0] != '\0')
			add_history(gen->input);
		//if (start_parsing(gen) == 1)
		//	return (0);
		free(gen->input);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data				gen;
	struct sigaction	sa;

	(void)ac, (void)env, (void)av;
	gen = (t_data){0};
	gen.env = env;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_sigaction = signals;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
	if (start(&gen) == 1)
		return (1);
	return (0);
}
