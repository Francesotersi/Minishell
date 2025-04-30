/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:43:01 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/29 15:40:27 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../Ssj_libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include "../minishell.h"

typedef struct s_exec	t_exec;
typedef int				(*t_builtin)(char **, t_exec *);
typedef struct s_token t_token;

/*
typedef struct s_token
{
	char			*content;
	int				id;
	int				prior;
	unsigned int	type:4;
}	t_token;*/

struct s_exec
{
	t_builtin		*builtins;
	int				*pid_list;
	char			***commands;
	char			***env;
	int				*env_size;
	int				*last_env;
	char			**path;
	char			*which_cmd;
	void			*main_struct_pointer;
	int				*here_doc_fds;
	int				*proc_sub_fds;
	int				*proc_sub_temp_fds;
	int				*exit_status;
	int				pipe_fds[2];
	int				last_in;
	int				last_out;
	int				cmd_num;
	int				curr_cmd;
	int				last_cmd_done;
	int				stdin_fd;
	int				stdout_fd;
	int				prior_layer;
	int				at_least_one_pipe:1;
	int				debug:1;
};

typedef struct s_wildcard
{
	char	*old_str;
	char	*search;
	char	*dir_path;
	int		start_len;
	int		end_len;
	int		dir_size;
}t_wildcard;

typedef struct s_debug_data
{
	char	***matrix;
	char	*temp;
	char	*filename1;
	char	*filename2;
	char	**env;
	t_token	*tokens;
	int		exit_status;
	int		last_env;
	int		env_size;
	int		fd_to_close;
}	t_debug_data;

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
	PARENTHESIS,
	RED_SUBSHELL,
	NONE,
};

enum e_builtin
{
	B_ECHO = 1,
	B_CD = 2,
	B_PWD = 3,
	B_EXPORT = 4,
	B_UNSET = 5,
	B_ENV = 6,
	B_EXIT = 7,
	BUILT_N = 8,
};

enum e_permissions
{
	INFILE = O_RDONLY,
	INFILE_DOC = O_RDWR | O_CREAT,
	OUTFILE_TRUNC = O_RDWR | O_CREAT | O_TRUNC,
	OUTFILE_APPEND = O_RDWR | O_CREAT | O_APPEND,
};

enum e_exec_errors
{
	NO_ERR,
	E_ARGS,
	E_MALLOC,
	E_OPEN,
	E_FORK,
	E_NOENV,
	E_ENV_PARSING,
	E_CD_ARGS,
	E_CD_PATH,
	E_CD_NOHOME,
	E_EXIT_NUMERIC,
	E_EXIT_ARGS,
	E_CMD_NOTFOUND,
	E_IS_DIRECTORY,
	E_PERMISSION_DENIED,
};

enum e_sub_strlen
{
	INCL,
	EXCL,
};

enum e_environment
{
	ENV_NO_EQ_PLUS = 0,
	ENV_NAME_SIZE = 1,
	ENV_CONT_SIZE = 2,
	ENV_WHICH_VAL = 3,
};

enum e_bools
{
	_STOP = 2,
	_YES = 1,
	_NO = 0,
};

//SECTION - Main function

int		execute(t_token *tokens, void *data, int debug);
int		execute_loop(t_token *token, t_exec *exec);

//SECTION Memory management

void	alloc_memory(t_exec *exec, t_token *token, int cmd_num);
void	free_memory(t_exec *memory);
void	*free_debug_data(t_debug_data *data);
void	get_main_struct_data(t_exec *exec, void *data, int debug);
void	close_and_reset(int *fd);

//SECTION - Utils

void	*_free_matrix(char **matrix);
void	*_free_three_d_matrix(char ***matrix);
char	*_ft_strjoin_free(char *s1, char *s2);
int		bigger(int n1, int n2);
int		count_commands(t_exec *exec, t_token *tokens);
int		is_red_sign(int sign);
int		is_exec_sep(int sign);
int		is_red_input_sign(int sign);
int		is_red_output_sign(int sign);
int		is_a_builtin_cmd(char *cmd);
int		_sub_strlen(char *s, char *charset, int mode);
int		_sub_strcpy(char *dest, char *src, char *charset, int mode);
int		double_cmp(char *s1, char *s2, int s1_len, int ignore_n_char);
char	*_cut_string(char *string, size_t start, size_t end);
char	*_cat_string(char *src, char *catstr, size_t start, int which_free);
int		set_exit_status(t_exec *exec, int exit_status);
char	*_reverse_split(char **matrix, char separator);
int		_reverse_strncmp(char *s1, char *s2, int len);
void	sort_matrix(char **matrix);
void	write_here_doc(char *line, t_exec *exec, int fd);
void	close_all(t_exec *exec);
int		find_command_argument_index(t_exec *exec, t_token *token);
void	find_command_id(t_exec *exec, t_token *token);
int		proc_sub_num(t_token *token);
int		deepest(t_token *token);
void	save_process_substitution_fd(t_exec *exec, int proc_sub_fd);
void	close_temp_files(t_exec *exec);
void	dup_and_reset(int *new_fd, int old_fd);
void	next_token(t_token **token, int search1, int search2, int search3);
void	next_cmd_block(t_token **token, int layer, bool accept_deeper_token);
void	skip_deeper_layers(t_token **token, int layer);
int		count_in_layer(t_token *token, int layer);
int		cmd_block_len(t_token *token, int layer);
void	goto_valid_block(t_exec *exec, t_token **token);
void	tok_next(t_token **token, int chr, int layer, bool accept_deeper_tok);
bool	detect_pipe(t_token *token, int getfd, int layer);

//SECTION - Environment management

int		cpy_env(char **old_env, char ***new_env, int *env_size, int *last_env);
int		expand_env(char ***env, int *env_size, t_exec *exec);
char	*ft_getenv(char **env, char *search, int *where);
int		env_pars(char *item, int *no_eq_plus, int *name_size, int *cont_size);
char	*get_pwd_address(char **env);

//SECTION Preparing data: modify tokens, env path, files, commands' path

void	merge_tokens(t_token *token, int debug);
void	prepare_here_docs(t_exec *exec, t_token *token);
int		get_commands_data(t_exec *exec, t_token *token);
int		get_paths_data(t_exec *exec, t_token *token);
int		get_file_data(t_exec *exec, t_token *token);

//SECTION Error and prints

int		error(int error_type, t_exec *memory);
int		exit_process(t_exec *exec);
int		bash_message(int message, char *file);
int		is_a_valid_executable(t_exec *exec, int i);
int		_fd_printf(int fd, const char *str, ...);

//SECTION - Builtin

int		ft_echo(char **args, t_exec *exec);
int		ft_cd(char **args, t_exec *exec);
int		ft_pwd(char **args, t_exec *exec);
int		ft_export(char **args, t_exec *exec);
int		ft_unset(char **args, t_exec *exec);
int		ft_env(char **args, t_exec *exec);
int		ft_exit(char **args, t_exec *exec);

//SECTION - Bonus

int		convert_wildcard(char *old_str, char **new_str);
int		manage_parenthesis(t_exec *exec, t_token **token, int getfd);
int		get_subshell_filename(t_exec *exec, t_token **token, int cmd_num);

#endif