/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:40:55 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/14 11:50:38 by ftersill         ###   ########.fr       */
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
		if (RL_ISSTATE(RL_STATE_READCMD))
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);	
			rl_redisplay();
		}
	}
	else if (signal == SIGQUIT)
	{
		exit_code_sig_received = CTRL_BACK;
		write(1, "Quit (core dumped)\n", 20);
		if (RL_ISSTATE(RL_STATE_READCMD))
		{
			rl_on_new_line();
			rl_replace_line("", 0);	
			rl_redisplay();
		}
	}
}

void	heredoc_signal(int signal, siginfo_t *info, void *s)
{
	(void)info;
	(void)s;
	if (signal == SIGINT)
	{
		exit_code_sig_received = CTRL_C;
		write(2, 
		"bash: warning: here-document at line 2 delimited by end-of-file",
		64);
		close(0);
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
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	assign_signal_exit_code(t_data *gen)
{
	if (exit_code_sig_received == CTRL_C)
	{
		exit_code_sig_received = 0;
		gen->exit_code = 130;
	}
	else if (exit_code_sig_received == CTRL_BACK)
	{
		exit_code_sig_received = 0;
		gen->exit_code = 131;
	}
}
