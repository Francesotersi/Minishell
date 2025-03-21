/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:53:39 by ftersill          #+#    #+#             */
/*   Updated: 2025/03/21 11:36:15 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// -CTRL-backslash = SIGQUIT
// -CTRL-C = SIGINT
// -CTRL-D command is controlled in the start() function cause 
//		it sends a NULL string to readline()
void	signals(int signal, siginfo_t *info, void *s)
{
	(void)info;
	(void)s;
	if (signal == SIGQUIT)
	{
		
	}
	else if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

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
