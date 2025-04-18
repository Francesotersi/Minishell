/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:53:39 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/18 08:44:29 by ftersill         ###   ########.fr       */
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
			return(write(1, "exit\n", 5), free(gen->input), 0);
		if (gen->input[0] != '\0')
			add_history(gen->input);
		if (start_lexing(gen) == -1)
			return (1);
		free(gen->input);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data				gen;
	struct sigaction	sa;

	(void)ac, (void)av;
	gen = (t_data){0};
	if (cpy_env(env, &gen.env, &gen.env_size, &gen.last_env) != 0)
		return (/* malloc error */1);
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_sigaction = signals;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
	_free_matrix(gen.env);
	if (start(&gen) == 1)
		return (1);
	return (0);
}
