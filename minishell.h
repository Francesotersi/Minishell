/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:56:23 by ftersill          #+#    #+#             */
/*   Updated: 2025/03/24 09:54:47 by ftersill         ###   ########.fr       */
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
# include "parsing/parsing.h"
# include "executor/executor.h"

enum e_permission
{
	INFILE = O_CREAT | O_APPEND,	
};

typedef struct s_data
{
	char	*input;
	int		exit_code;
	char	**env;
	
} t_data;

typedef struct s_token
{
	char	*str;	// contenuto del token
	int		type;	// tipo del token
	int		id;		// posizione del token nell`input
	int		prior;	// priorita`
} t_token;

//signals
void	signals(int signal, siginfo_t *info, void *s);
int		which_signal_received(void);

#endif