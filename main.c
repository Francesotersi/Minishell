/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:53:39 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/22 12:53:17 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// readline ritorna una stringa da freeare ad ogni input
int	start(t_data *gen, int i, int j)
{
	while (1)
	{
		reset_standard_signal();
		gen->input = readline("Minishell$> ");
		assign_signal_exit_code(gen);
		if (!gen->input)
			break ;
		if (gen->input[0] != '\0')
			add_history(gen->input);
		if (ft_strncmp(gen->input, "", ft_strlen(gen->input)))
		{
			i = start_lexing(gen, j);
			if (i == -1)
				return (1);
			else if (i != 2)
			{
				execute(gen->token, (void *)gen);
				assign_signal_exit_code(gen);
				free_all(gen->token, gen);
			}
		}
		free(gen->input);
	}
	write(1, "exit\n", 5);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data				gen;
	int					i;
	int					j;

	i = 0;
	j = 0;
	(void)ac, (void)av;
	gen = (t_data){0};
	if (cpy_env(env, &gen.env, &gen.env_size, &gen.last_env) != 0)
		return (ft_error("env error", -1, &gen, ""), 1);
	if (start(&gen, i, j) == 1)
		return (1);
	_free_matrix(gen.env);
	close(0);
	close(1);
	close(2);
	return (gen.exit_code);
}
