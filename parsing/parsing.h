/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:05:40 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/17 12:08:10 by ftersill         ###   ########.fr       */
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
int		ft_strcmp(char *s1, char *s2);

// struct_alloc.c
int		alloc_str_token(t_token *token, t_data *gen);

// remove_quotes.c
void	remove_quotes_token(t_token *token, t_data *gen);

// define_token.c
int		define_token_arg(t_token *token, t_data *gen);

// temp_files_from_ale.c
char	*_cut_string(char *string, size_t start, size_t end);
char	*get_env(char **env, char *search);
int		_sub_strlen(char *s, char *charset, int mode);
int		cpy_env(char **old_env, char ***new_env, int *env_size, int *last_env);
char	*ft_getenv(char **env, char *search, int *where);
void	*_free_matrix(char **matrix);

// expand_env.c
void	expanding_variables(t_token *token, t_data *gen);

#endif