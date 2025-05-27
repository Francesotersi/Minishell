/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cmd_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:35:44 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/27 11:03:48 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int		parse_prompt(char *s, int *i, char *t_quote, t_data *gen);
int		find_something(char *s, char searched, int *i, char *t_quote);
int		get_last_parenthesis(char *s, int dollar_i, int *last_p_i);
void	replace_line(char **s, int start, int end, t_data *gen);
void	stop_program(t_data *gen, int error_type);
char	*get_cmd_output(char *sub_cmd, t_data *gen);
int		get_subcmd_stdout_name(t_data *gen);
int		get_files(int backup_fds[2], int redir_fds[2], char *cmd, t_data *gen);
int		close_files(int backup_fds[2], int redir_fds[2], char del, t_data *gen);
void	run_sub_cmd(t_data *gen, int backup_fds[2], int redir_fds[2]);
void	read_output(t_data *gen, char **s, int result_fd);

int	command_substitution(char **prompt, t_data *gen)
{
	int		i;
	int		dollar_i;
	int		last_p_i;
	char	t_quote;

	i = 0;
	t_quote = 0;
	while ("Loop: expand all valid $() in prompt")
	{
		dollar_i = parse_prompt(*prompt, &i, &t_quote, gen);
		if (!(*prompt)[i])
			return (0);
		else if (dollar_i == -1)
			continue ;
		else if (dollar_i == -2)
			return (1);
		_cut_string(*prompt, dollar_i, dollar_i + 1);
		if (get_last_parenthesis(*prompt, dollar_i, &last_p_i) == 1)
			return (ft_error("syntax error near quote", 2, gen, ""), 1);
		replace_line(prompt, dollar_i, last_p_i, gen);
	}
}

void	replace_line(char **s, int start, int end, t_data *gen)
{
	char	*line;

	(*s)[end] = 0;
	line = get_cmd_output(*s + start, gen);
	(*s)[end] = ' ';
	_cut_string(*s, start, end);
	if (line)
	{
		*s = _cat_string(*s, line, start, 3);
		if (!*s)
			stop_program(gen, E_MALLOC);
	}
}

char	*get_cmd_output(char *sub_cmd, t_data *gen)
{
	int		backup_fds[2];
	int		redir_fds[2];
	char	*line;
	int		result_fd;

	if (get_subcmd_stdout_name(gen) == 1)
		stop_program(gen, E_MALLOC);
	if (get_files(backup_fds, redir_fds, sub_cmd, gen) == 1)
		stop_program(gen, E_OPEN);
	run_sub_cmd(gen, backup_fds, redir_fds);
	dup2(backup_fds[0], STDIN_FILENO);
	dup2(backup_fds[1], STDOUT_FILENO);
	line = NULL;
	result_fd = open(gen->subcmd_stdout, O_RDWR | O_CREAT, 0777);
	close_files(backup_fds, redir_fds, _YES, gen);
	if (result_fd == -1)
		stop_program(gen, E_OPEN);
	read_output(gen, &line, result_fd);
	close(result_fd);
	return (line);
}

int	get_files(int backup_fds[2], int redir_fds[2], char *cmd, t_data *gen)
{
	backup_fds[0] = dup(STDIN_FILENO);
	backup_fds[1] = dup(STDOUT_FILENO);
	redir_fds[0] = open(".subcmd_stdin", O_RDWR | O_CREAT, 0777);
	redir_fds[1] = open(gen->subcmd_stdout, O_RDWR | O_CREAT, 0777);
	if (!redir_fds[0] || !redir_fds[1])
		return (close_files(backup_fds, redir_fds, _YES, gen));
	write(redir_fds[0], cmd, ft_strlen(cmd));
	close(redir_fds[0]);
	redir_fds[0] = open(".subcmd_stdin", O_RDWR | O_CREAT, 0777);
	if (!redir_fds[0])
		return (close_files(backup_fds, redir_fds, _YES, gen));
	unlink(".subcmd_stdin");
	dup_and_reset(&redir_fds[0], STDIN_FILENO);
	dup_and_reset(&redir_fds[1], STDOUT_FILENO);
	return (0);
}

void	run_sub_cmd(t_data *gen, int backup_fds[2], int redir_fds[2])
{
	pid_t	pid;
	char	**empty_matrix;

	pid = fork();
	if (pid < 0)
	{
		close_files(backup_fds, redir_fds, _YES, gen);
		stop_program(gen, E_FORK);
	}
	else if (pid == 0)
	{
		empty_matrix = (char **)ft_calloc(2, sizeof(char *));
		close_files(backup_fds, redir_fds, _NO, gen);
		if (!empty_matrix)
			stop_program(gen, E_MALLOC);
		empty_matrix[0] = ft_strdup("");
		if (!empty_matrix[0])
			return (_free_matrix(empty_matrix), stop_program(gen, E_MALLOC));
		execve(gen->minishell_path, empty_matrix, gen->env);
		empty_matrix = _free_matrix(empty_matrix);
		stop_program(gen, E_FORK);
	}
	waitpid(pid, NULL, 0);
}
