/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:56:23 by ftersill          #+#    #+#             */
/*   Updated: 2025/03/19 12:14:29 by ftersill         ###   ########.fr       */
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
# include "parsing/parsing.h"
# include "executor/executor.h"

// int	signal = 0;

enum e_permission
{
	INFILE = O_CREAT | O_APPEND,	
};

typedef struct s_data
{
	char	*input;
	int		exit_code;
	
} t_data;

#endif