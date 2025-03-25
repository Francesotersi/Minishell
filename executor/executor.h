/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:43:01 by alerusso          #+#    #+#             */
/*   Updated: 2025/03/25 17:10:25 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../Ssj_libft/libft.h"

typedef struct s_token
{
	char			*content;
	unsigned int	id;
	unsigned int	prior;
	unsigned int	type:4;
}t_token;

typedef struct s_exec
{
	int				*pid_list;
	char			**commands;
	char			**path;
	int				*fds;
	char			**files_to_trash;
	char			*temp;
	char			***options;
	int				*red_input;
	int				*red_output;
	int				last_in;
	int				last_out;
	int				cmd_num;
	unsigned int	here_doc_bool:1 * 1;
	unsigned int	append_out:1 * 1;
	unsigned int	pipe:1 * 1;
}				t_exec;

enum e_types
{
	COMMAND,
	ARGUMENT,
	FILES,
	RED_OUT,
	RED_IN,
	RED_O_APPEND,
	HERE_DOC,
	PIPE,
	AND,
	OR,
	WILDCARD,
};

enum e_permissions
{
	INFILE = O_RDONLY,
	HERE_DOC = O_RDWR,
	OUTFILE_TRUNC = O_RDWR | O_CREAT | O_TRUNC,
	OUTFILE_APPEND = O_RDWR | O_CREAT | O_APPEND,
};

enum e_storage
{
	STORE,
	RECEIVE,	
};

enum e_exec_errors
{
	NONE,
	E_ARGS,
	E_MALLOC,
};

enum e_sub_strlen
{
	INCL,
	EXCL,
};

enum e_bools
{
	YES = 1,
	NO = 0,
};

//SECTION - Main function

int	execute(t_token *tokens);

//SECTION Memory management

t_exec	*storage(t_exec *update, int mode);
int		alloc_memory(t_exec **exec, int cmd_num);
void	free_memory(void);

//SECTION - General

void	*_free_matrix(char **matrix);
void	*_free_three_d_matrix(char ***matrix);
int		_sub_strlen(char *s, char *charset, int mode);
int		count_commands(t_token *tokens);
int		is_red_sign(int sign);
int		is_exec_sep(int sign);

//SECTION Preparing data: env path, files, commands' path

int		get_execution_data(t_exec *exec, t_token *token);
int		get_file_data(t_exec *exec, t_token *token);

//SECTION Error prints

int	error(int error_type);

#endif
