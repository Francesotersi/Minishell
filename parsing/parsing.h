/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:05:40 by ftersill          #+#    #+#             */
/*   Updated: 2025/03/24 10:01:11 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../minishell.h"

typedef struct s_data t_data;
typedef struct s_token t_token;

//  start_lexing.c
int		start_lexing(t_data *gen);

//  fill_struct.c
void     fill_struct(t_token *token, t_data *gen);

//  utils.c
void    printf_struct(t_token *token, t_data *gen);

#endif