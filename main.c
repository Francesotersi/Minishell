/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:53:39 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/27 16:37:27 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// readline ritorna una stringa da freeare ad ogni input
int	start(t_data *gen, int i, int j)
{
	while (1)
	{
		reset_standard_signal();
		gen->input = readline(PROMPT);
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
				free_all(gen->token, gen, true);
			}
		}
		free(gen->input);
		gen->input = NULL;
	}
	return (write(1, "exit\n", 5), 0);
}

int	get_minishell_path(t_data *gen)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	gen->minishell_path = ft_strjoin(pwd, PROG_NAME);
	free(pwd);
	if (!gen->minishell_path)
		return (1);
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
	if (get_minishell_path(&gen) == 1)
		return (ft_error("malloc error", -1, &gen, ""), 1);
	if (start(&gen, i, j) == 1)
		return (1);
	_free_matrix(gen.env);
	free(gen.minishell_path);
	free(gen.subcmd_stdout);
	close(0);
	close(1);
	close(2);
	return (gen.exit_code);
}
