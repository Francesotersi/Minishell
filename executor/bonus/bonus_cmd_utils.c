/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:43:30 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/27 10:45:02 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	stop_program(t_data *gen, int error_type)
{
	t_exec	exec;

	exec = (t_exec){0};
	exec.main_struct_pointer = gen;
	error(error_type, &exec);
}

int	close_files(int backup_fds[2], int redir_fds[2], char del, t_data *gen)
{
	if (del)
	{
		unlink(".subcmd_stdin");
		unlink(gen->subcmd_stdout);
	}
	close_and_reset(&backup_fds[0]);
	close_and_reset(&backup_fds[1]);
	close_and_reset(&redir_fds[0]);
	close_and_reset(&backup_fds[1]);
	return (1);
}

void	read_output(t_data *gen, char **s, int result_fd)
{
	char	*line;
	int		prompt_len;

	prompt_len = ft_strlen(PROMPT);
	line = get_next_line_bonus(result_fd);
	while (line)
	{
		if (line[0] == '\n' || !ft_strncmp(line, PROMPT, prompt_len))
		{
			free(line);
			line = get_next_line_bonus(result_fd);
			continue ;
		}
		line[ft_strlen(line) - 1] = ' ';
		if (!*s)
		{
			*s = ft_strdup(line);
			free(line);
		}
		else
			*s = _ft_strjoin_free(*s, line);
		if (!*s)
			return (close(result_fd), stop_program(gen, E_MALLOC));
		line = get_next_line_bonus(result_fd);
	}
}

int	get_subcmd_stdout_name(t_data *gen)
{
	char	*shell_level;

	free(gen->subcmd_stdout);
	shell_level = get_env(gen->env, "SHLVL");
	if (!shell_level)
	{
		gen->subcmd_stdout = ft_strdup(".subcmd_stdout");
		return (gen->subcmd_stdout == NULL);
	}
	gen->subcmd_stdout = ft_strjoin(".subcmd_stdout", shell_level);
	return (gen->subcmd_stdout == NULL);
}

int	get_last_parenthesis(char *s, int dollar_i, int *last_p_i)
{
	int		layer;
	int		i;
	char	t_quote;

	i = dollar_i;
	t_quote = 0;
	layer = 1;
	while (s[i])
	{
		if (t_quote == s[i])
			t_quote = 0;
		else if ((!t_quote) && (s[i] == '\'' || s[i] == '\"'))
			t_quote = s[i];
		else if (!t_quote && s[i] == '(')
			layer += 1;
		else if (!t_quote && s[i] == ')')
			layer -= 1;
		if (layer == 0)
			break ;
		++i;
	}
	if (!s[i])
		return (1);
	*last_p_i = i;
	return (0);
}
