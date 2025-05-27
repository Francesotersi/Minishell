/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:05:40 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/27 15:58:13 by alerusso         ###   ########.fr       */
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
int		start_lexing(t_data *gen, int j);
int		num_token(char *str, t_data *gen);
int		count_char_token(char *str, int *i, int *len, t_data *gen);
int		operator_token(char *str, int *i, int *len, t_data *gen);
int		quotes_token(char *str, int *i, int *len, int *temp);

//  fill_struct.c
void	fill_struct(t_token *token, t_data *gen);

//  utils.c
void	token_struct_init(t_token *token, t_data *gen);
void	printf_struct(t_token *token, t_data *gen);
void	free_all(t_token *token, t_data *gen, bool check);
void	free_token(t_token *token, t_data *gen);
void	free_struct(t_token *token);

// utils_2.c
void	skip_single_quotes(char *str, int *i);
void	ft_error(char *str, int exit_c, t_data *gen, char *token);
int		heredoc_d_case(t_token *token, int *id);
void	if_inside_quote(t_token *token, t_data *gen);
int		num_token(char *str, t_data *gen);

// struct_alloc.c
int		alloc_str_token(t_token *token, t_data *gen);

// remove_quotes.c
int		remove_quotes_token(t_token *token);
void	fix_gen_token_num(t_token *token, t_data *gen);

// define_token.c
int		define_token_and_parenthesis(t_token *token, t_data *gen);

// define_token_2.c
int		is_redirection(t_token *tok, t_data *gen, int *id);
int		is_redirection_2(t_token *tok, int *id);
int		is_cmd_2(t_token *tok, int *id);
int		is_cmd(t_token *tok, t_data *gen);

// expand_env.c
int		expanding_variables(t_token *token, t_data *gen);

// expand_env_2.c
char	*what_to_search(t_token *token, int *i);
void	expand_exit_code(t_token *token, t_data *gen, int *id, int *i);
void	expand_exit_code_2(t_token *token, t_data *gen, int *i,
			char *exit_code);
void	insert_exit_code(t_token *token, int *i, int e_l, char *exit_code);
void	skip_env_var(t_token *token, int *i, char *temp);

// parenthesis.c
int		prior_of_token(t_token *token, t_data *gen);
int		count_parenthesis(t_token *token, t_data *gen);

// expand_wildcard.c
int		expand_wildcard(t_token *token, t_data *gen);
int		find_char(t_token *token, char c);

// expand_wildcard_2.c
t_token	*reallocation_and_all(t_data *gen, t_token *token);
int		intersection(t_token *token, t_data *gen);
int		actual_removal_2(t_token *token, char *temp, int *i, int *j);

// parser.c
int		actual_parser(t_token *token, t_data *gen);

// parser_2.
int		even_more_cases(t_token *tok, int *id, t_data *gen);

// ambiguous_redir.c
int		ambiguous_redir(t_token *token, t_data *gen);

#endif