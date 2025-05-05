/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:05:40 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/05 15:19:16 by ftersill         ###   ########.fr       */
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
# include "../enum.h"

// enum e_types
// {
// 	COMMAND = 0,
// 	ARGUMENT = 1,
// 	FILES = 2,
// 	RED_OUT = 3,
// 	RED_IN = 4,
// 	RED_O_APPEND = 5,
// 	HERE_DOC = 6,
// 	PIPE = 7,
// 	AND = 8,
// 	OR = 9,
// 	PARENTHESIS = 10,
// 	RED_SUBSHELL = 11,
// 	NONE = 12,
// };

typedef struct s_data	t_data;
typedef struct s_token	t_token;

//  start_lexing.c
int		start_lexing(t_data *gen);

//  fill_struct.c
void	fill_struct(t_token *token, t_data *gen);

//  utils.c
void	token_struct_init(t_token *token, t_data *gen);
void	printf_struct(t_token *token, t_data *gen);
void	free_all(t_token *token, t_data *gen);
void	free_token(t_token *token, t_data *gen);
void	free_struct(t_token *token);

// utils_2.c
void	skip_single_quotes(char *str, int *i);

// struct_alloc.c
int		alloc_str_token(t_token *token, t_data *gen);

// remove_quotes.c
void	remove_quotes_token(t_token *token, t_data *gen);

// define_token.c
int		define_token_and_parenthesis(t_token *token, t_data *gen);

// expand_env.c
void	expanding_variables(t_token *token, t_data *gen);

// expand_env_2.c
char	*what_to_search(t_token *token, int *i);
void	expand_exit_code(t_token *token, t_data *gen);
void	expand_exit_code_2(t_token *token, t_data *gen, int *i,
			char *exit_code);
void	insert_exit_code(t_token *token, int *i, int e_l, char *exit_code);
void	skip_env_var(t_token *token, int *i, char *temp);

// parenthesis.c
int		prior_of_token(t_token *token, t_data *gen);
int		count_parenthesis(t_token *token, t_data *gen);

// define_token_2.c
int		is_redirection(t_token *tok, t_data *gen, int *id);
int		is_redirection_2(t_token *tok, int *id);

#endif