/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:05:40 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/14 08:42:05 by ftersill         ###   ########.fr       */
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
void	fill_struct(t_token *token, t_data *gen);

//  utils.c
void	token_struct_init(t_token *token, t_data *gen);
void	printf_struct(t_token *token, t_data *gen);
void	free_all(t_token *token, t_data *gen);
void	free_token(t_token *token, t_data *gen);

// struct_alloc.c
int		alloc_str_token(t_token *token, t_data *gen);

// remove_quotes.c
void	remove_quotes_token(t_token *token, t_data *gen);

#endif