/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:40:55 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/22 12:52:56 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// -CTRL-backslash = SIGQUIT
// -CTRL-C = SIGINT
// -CTRL-D command is controlled in the start() function cause 
//		it sends a NULL string to readline()

// aggiungere exit code

int	g_exit_code_sig_received = 0;

void	execve_signal(int signal, siginfo_t *info, void *s)
{
	(void)info;
	(void)s;
	if (signal == SIGINT)
	{
		g_exit_code_sig_received = CTRL_C;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (signal == SIGQUIT)
	{
		g_exit_code_sig_received = CTRL_BACK;
		write(2, "Quit (core dumped)\n", 20);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	heredoc_signal2(int signal)
{
	if (signal == SIGQUIT)
	{
		write(1, "\b\b", 2);
		write(1, "  ", 2);
		write(1, "\b\b", 2);
	}
}

void	heredoc_signal(int signal, siginfo_t *info, void *s)
{
	(void)info;
	(void)s;
	if (signal == SIGINT)
	{
		g_exit_code_sig_received = CTRL_C;
		close(0);
	}
}

void	signals(int signal, siginfo_t *info, void *s)
{
	(void)info;
	(void)s;
	if (signal == SIGINT)
	{
		g_exit_code_sig_received = CTRL_C;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	assign_signal_exit_code(t_data *gen)
{
	if (g_exit_code_sig_received == CTRL_C)
	{
		g_exit_code_sig_received = 0;
		gen->exit_code = 130;
	}
	else if (g_exit_code_sig_received == CTRL_BACK)
	{
		g_exit_code_sig_received = 0;
		gen->exit_code = 131;
	}
}
