/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:56:23 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/26 23:12:21 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "Minishell$> "
# define PROG_NAME "/minishell"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include "Ssj_libft/libft.h"
# include "parsing/parsing.h"
# include "executor/executor.h"

extern int	g_exit_code_sig_received;

typedef struct s_data
{
	char				*input;
	unsigned char		exit_code;
	int					token_num;
	char				**env;
	int					last_env;
	int					env_size;
	t_token				*token;
	char				*minishell_path;
	char				*subcmd_stdout;
}	t_data;

typedef struct s_token
{
	char	*content;
	int		type;
	int		id;
	int		prior;
	int		t_quote;
	int		cmd_num;
	int		is_expanded;
	bool	space_on_right;
}	t_token;

int		command_substitution(char **prompt, t_data *gen);

//signals
void	signals(int signal, siginfo_t *info, void *s);
void	heredoc_signal(int signal, siginfo_t *info, void *s);
void	assign_signal_exit_code(t_data *gen);
void	execve_signal(int signal, siginfo_t *info, void *s);
void	heredoc_signal2(int signal);

//set_signals.c
void	reset_standard_signal(void);
void	set_here_doc_signal(void);
void	set_execve_signal(void);
void	last_signal(int signal, siginfo_t *info, void *s);
void	set_last_signal(void);

#endif