/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:43:01 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/29 14:13:37 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../Ssj_libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include "../minishell.h"
# include "../enum.h"
# define DOC_NAME ".here_doc"

typedef struct s_exec	t_exec;
typedef int				(*t_builtin)(char **, t_exec *);
typedef struct s_token	t_token;

//NOTE - Valgrind home
/*
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
--trace-children=yes --track-origins=yes -s -q \
--suppressions=/home/alerusso/Common_core/Minishell-test/executor/v.supp \
./exe.out 1
*/

//ANCHOR - Data structures

/*REVIEW - execution data structure

	Every time a command is called, without syntax error,
	The program allocs memory for this structure.
	
-	*builtins:	an array of functions.
	//			using those brings to builtin functions
	//
-	*pid_list:	an array of pid.
	//			0 refers to the command in token->cmd_num == 0.
	//			for ls | grep, ls pid goes in pid_list[0]
	//			for BUILTIN, the exit code is set in this array,
	//			setted negative (ex: Exit Code 5 ---> -5).
	//			so, for every command, the exit code is taken
	//			with waitpid, or making the pid value positive for builtins
	//
	***commands:3d matrix of commands.
	//			commands = {ls, NULL}, {grep, .c, NULL}
	//
-	***env:		a pointer to the env matrix from main data struct
	//
-	*env_size:	a pointer to the env_size int from main data struct.
	//			represents the env matrix allocated memory size
	//
	*last_env:	a pointer to the last_env int from main data struct.
	//			represents the last env element's index
	//
-	**path:		a matrix made from the env variable "path".
	//			stores all programs possible paths
	//
-	*which_cmd:	a string that stores what kind of builtin
	//			a command is.
	//			a non builtin command has value 0.
	//			otherwise, see builtin enum.
	//			echo ciao | grep c | exit 7 
	//			which_cmd = [1, 0, 7]
	//
-	*here_doc_fds:an array of here_docs fds.
	//			0 refers to the here doc in token->cmd_num == 0.
	//			for <<EOF1 <<EOF2 | <<EOF3, EOF2 fd goes in
	//			here_doc_fds[0], EOF3 fd goes in
	//			here_doc_fds[1]. EOF1 is created, but not saved.
	//			here_doc_fds[i] is closed at the end
	//			of command_block[i]
	//
-	*proc_sub_fds:an array of process substitution fds.
	//			every time there's a <(ls), a fd 
	//			containing the output of the subshell
	//			is created.
	//			proc_sub_fds stores all of these fds
	//			for every command block.
	//			for cat <(ls) <(ls -R) | cat, 
	//			proc_sub_fds = [fd of <(ls), fd of <(ls -R)]
	//			proc_sub_fds are all closed at the end of
	//			a command block
	//
-	*proc_sub_temp_fds:stores all fds that cannot be
	//			closed in a subshell.
	//			for cat <(ls), <(ls) process cannot close
	//			original STDOUT (terminal) and the STDIN pipe
	//			end created before the process.
	//			this array has size equal to:
	//			(cmd_block with biggest proc sub num) * 2.
	//			this data is found with proc_sub_num() ft
	//
-	*exit_code:a pointer to the main struct exit code
	//
	pipe_fds[2]:an array that stores, with pipes, 
	//			pipe STDIN and pipe STDOUT,
	//			in pipe_fds[0] and pipe_fds[1]
	//
	last_in:	last input file token id in a 
	//			command block.
	//			for "cat <f1 <<EOF <f2", last_in == 3
	//
	last_out:	last output file token id in a 
	//			command block.
	//			for "cat >f1 >>f2 >f3", last_out == 3
	//
	curr_cmd:	current command block that is being
	//			executed
	//
	//
	last_cmd:	number of command blocks.
	//			for ls | grep .c
	//			last_cmd == 2
	//
	stdin_fd:	an fd that stores a dup of STDIN
	//
	stdout_fd:	an fd that stores a dup of STDOUT
	//
	prior_layer:current priority layer (parenthesis).
	//			execute_loop is called recursively in 
	//			parenthesis: at the start of a loop,
	//			prior_layer is set to current token prior.
	//			for echo <(cat <(ls))
	//			echo	---->	prior_layer == 0
	//			cat		---->	prior_layer == 1
	//			ls		---->	prior_layer == 2
	//
	at_least_one_pipe:bool that shows if, in the whole
	//			command, there is at least one pipe.
	//			It is updated at the start of
	//			execution_loop and after a && or ||
	//
	debug:		bool that shows if we are in 
	//			execution debug mode or not.
	//			Execution debug mode will not be
	//			included in final project
*/
struct s_exec
{
	t_builtin		*builtins;
	t_token			*first_token;
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
	unsigned char	*exit_code;
	char			*minishell_path;
	int				pipe_fds[2];
	int				last_in;
	int				last_out;
	int				curr_cmd;
	int				last_cmd;
	int				stdin_fd;
	int				stdout_fd;
	int				prior_layer;
	int				at_least_one_pipe:1;
	int				file_not_found:1;
};

/*REVIEW - wildcard data structure

	Every time a wildcard is parsed, the program
	allocs memory for this structure.
	Example:	Common_core/Libft/.h
	
-	*old_str:	The starting string to expand.
	//			"Common_core/Libft/.h"
	//
-	*search:	The occurence to search.
	//			"*.h"
	//
-	*dir_path:	The folder to search where.
	//			"Common_core/Libft/"
	//
-	dir_size:	The number of element in the directory.
	//			55
	//
*/
typedef struct s_wildcard
{
	char	*old_str;
	char	*search;
	char	*dir_path;
	int		dir_size;
}	t_wildcard;

//ANCHOR - 	List of functions called in all execution part.
//			Section name is folder name.

//SECTION -	Bonus

int		convert_wildcard(char *old_str, char **new_str);
int		manage_parenthesis(t_exec *exec, t_token **token, int getfd);
int		get_subshell_filename(t_exec *exec, t_token **token, int cmd_num);

//SECTION -	Builtin

int		ft_cd(char **args, t_exec *exec);
int		ft_echo(char **args, t_exec *exec);
int		ft_env(char **args, t_exec *exec);
int		ft_exit(char **args, t_exec *exec);
int		exit_process(t_exec *exec);
int		ft_export(char **args, t_exec *exec);
int		ft_pwd(char **args, t_exec *exec);
int		ft_unset(char **args, t_exec *exec);

//SECTION -	Environment management

//	NOTE -	Functions to use in main program

int		cpy_env(char **old_env, char ***new_env, int *env_size, int *last_env);
char	*get_env(char **env, char *search);
char	*get_pwd_address(char **env);

//	NOTE -	Functions to use in execution part only

int		realloc_env(char ***env, int *env_size, t_exec *exec);
char	*ft_getenv(char **env, char *search, int *where);
int		env_pars(char *item, int *no_eq_plus, int *name_size, int *cont_size);
int		increase_shell_level(char **env);
int		change_shell_name(char **env);

//SECTION -	Execution main

int		execute(t_token *tokens, void *data);
void	execute_loop(t_token *token, t_exec *exec);
int		wait_everyone(t_exec *exec);

//	NOTE -	Error and prints

int		error(int error_type, t_exec *memory);
int		bash_message(int message, char *file);

//SECTION -	Execution preparations

void	merge_tokens(t_token *token);
int		prepare_here_docs(t_exec *exec, t_token *token);
int		get_commands_data(t_exec *exec, t_token *token);
int		get_paths_data(t_exec *exec);
int		get_file_data(t_exec *exec, t_token *token, bool do_pipe);

//SECTION -	Memory management

void	alloc_memory(t_exec *exec, t_token *token, int cmd_num);
void	free_memory(t_exec *memory);
void	get_main_struct_data(t_exec *exec, void *data);
void	create_empty_matrix(t_exec *exec, int cmd_num);

//SECTION -	Utils

//	NOTE -	printf_fd:	a ft_printf that accepts an fd

int		_fd_printf(int fd, const char *str, ...);

//	NOTE -	utils_count:Get crucial data from token

int		count_commands(t_token *token);
int		find_command_argument_index(t_exec *exec, t_token *token);
int		proc_sub_num(t_token *token);
int		deepest(t_token *token);
int		matrix_size(char **matrix);

//	NOTE -	debug:		Prints all token, delimiting execution		

void	p_tok(t_token *token);
void	p_end(t_exec *exec);

//	NOTE -	fds:		Manage fds (close temp files, closing if fd >= 3...)

void	close_all(t_exec *exec);
void	save_process_substitution_fd(t_exec *exec, int proc_sub_fd);
void	close_temp_files(t_exec *exec);
void	close_and_reset(int *fd);
void	dup_and_reset(int *new_fd, int old_fd);
void	save_temp_fds(t_exec *exec, int fd1, int fd2, int do_pipe);
void	remove_temp_fds(t_exec *exec);

//	NOTE -	generic:	Various functions

int		bigger(int n1, int n2);
int		is_a_valid_executable(t_exec *exec, int i);
int		set_exit_code(t_exec *exec, int exit_code);
void	write_here_doc(char *line, t_exec *exec, int fd);
int		overflow_check(char *s, long long max, long long min, int limit_size);

//	NOTE -	matrix:		Matrix management

void	*_free_matrix(char **matrix);
void	*_free_three_d_matrix(char ***matrix);
char	*_reverse_split(char **matrix, char separator);
void	sort_matrix(char **matrix);
char	*lowest_ascii_matrix(char **matrix, char *current);

//	NOTE -	parenthesis:Skip token in parenthesis and much more

void	next_token(t_token **token, int search1, int search2, int search3);
void	next_cmd_block(t_token **token, int layer, bool accept_deeper_token);
void	skip_deeper_layers(t_token **token, int layer);
int		count_in_layer(t_token *token, int layer);
int		cmd_block_len(t_token *token, int layer);
void	goto_valid_block(t_exec *exec, t_token **token);
void	tok_next(t_token **token, int chr, int layer, bool accept_deeper_tok);
void	token_out_parenthesis(t_exec *exec, t_token **token, bool process_sub);
bool	detect_pipe(t_token *token, int getfd, int layer);
bool	check_proc_sub(t_exec *exec, t_token *token);

//	NOTE -	string:		String utilities

int		_sub_strlen(char *s, char *charset, int mode);
int		_sub_strcpy(char *dest, char *src, char *charset, int mode);
char	*_cut_string(char *string, size_t start, size_t end);
char	*_cat_string(char *src, char *catstr, size_t start, int which_free);
char	*_ft_strjoin_free(char *s1, char *s2);
int		_reverse_strncmp(char *s1, char *s2, int len);
int		double_cmp(char *s1, char *s2, int s1_len, int ignore_n_char);
char	*remove_plus(char *str);
char	*_ft_strrstr(const char *haystack, const char *needle);

//	NOTE -	tokencheck:	is_alpha for token types (is redirection sign? ecc.)

int		is_red_sign(int sign);
int		is_exec_sep(int sign);
int		is_red_input_sign(int sign);
int		is_red_output_sign(int sign);
int		is_a_builtin_cmd(char *cmd);

#endif