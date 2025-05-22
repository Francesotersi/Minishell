/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:56:23 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/22 11:10:20 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
}	t_data;

typedef struct s_token
{
	char	*content;	// contenuto del token
	int		type;	// tipo del token
	int		id;		// posizione del token nell`input
	int		prior;	// priorita`
	int		t_quote; //tipo di quote contenuta nel token
	int		cmd_num;
	int		is_expanded; //se il tok e` stato espanso o meno
	bool	space_on_right; //se e` presente uno spazio alla dx del tok
}	t_token;

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