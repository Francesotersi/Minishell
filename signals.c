/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:40:55 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/13 14:12:28 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// -CTRL-backslash = SIGQUIT
// -CTRL-C = SIGINT
// -CTRL-D command is controlled in the start() function cause 
//		it sends a NULL string to readline()

// aggiungere exit code

int	exit_code_sig_received = 0;

void	execve_signal(int signal, siginfo_t *info, void *s)
{
	(void)info;
	(void)s;
	if (signal == SIGINT)
	{
		exit_code_sig_received = CTRL_C;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		exit_code_sig_received = CTRL_BACK;
		write(1, "Quit (core dumped)\n", 20);
	}
}

void	heredoc_signal(int signal, siginfo_t *info, void *s) // heredoc con ctrl D passa all`heredoc successivo
{
	(void)info;
	(void)s;
	if (signal == SIGINT)
	{
		exit_code_sig_received = CTRL_C;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		write(1, "\b\b", 2);
		write(1, "  ", 2);
		write(1, "\b\b", 2);
	}
}

void	signals(int signal, siginfo_t *info, void *s)
{
	(void)info;
	(void)s;
	if (signal == SIGINT)
	{
		exit_code_sig_received = CTRL_C;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
