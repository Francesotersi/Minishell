/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:41:56 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/21 11:26:36 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	signals_check(char *line, int *fd, t_exec *exec);
static void	here_doc_loop(char **line, t_exec *exec);
static int	get_here_doc_file(char *limiter, t_exec *exec);

/*REVIEW - prepare_here_docs

//FIXME - Signals management is not implemented yet!

//		For every command block, we open all here_docs.
		However, we need to keep the fd only if the here_doc is 
		the last STDIN redirector.
		1)	We iterate through every token of the command block;
		2)	We gain the fd of the here doc. If a here doc already exists
			in the current command block, we close it.
*/
int	prepare_here_docs(t_exec *exec, t_token *token)
{
	int	i;

	while (token->content)
	{
		i = token->cmd_num;
		if (token->type == HERE_DOC)
		{
			if (exec->here_doc_fds[i])
				close_and_reset(&exec->here_doc_fds[i]);
			exec->here_doc_fds[i] = get_here_doc_file(token->content, exec);
			if (g_exit_code_sig_received == CTRL_C)
				return (CTRL_C);
		}
		++token;
	}
	return (0);
}

/*REVIEW - get_here_doc_file

//FIXME - Signals management is not implemented yet!

//	1)	We open a file named "here_doc";
	2)	We write "> ": a bash syntax string that means "Write here, user".
		The write process goes line per line. If user gives a special
		character, called LIMITER, the write process stops.
		Limiter is not written in here doc file.
	3)	We close and open here_doc file to move the cursor to the start
		of the line;
	4)	We return the new fd, if there are no errors.
		It will be saved in a here_doc_fds array, and closed at the end
		of its own command block.
*/
static int	get_here_doc_file(char *limiter, t_exec *exec)
{
	int		fd;
	char	*line;
	int		limiter_len;

	line = NULL;
	fd = open(DOC_NAME, INFILE_DOC, 0666);
	if (fd < 0)
		error(E_OPEN, exec);
	here_doc_loop(&line, exec);
	if (signals_check(line, &fd, exec) == 1)
		return (fd);
	limiter_len = ft_strlen(limiter);
	while ((line) && (double_cmp(limiter, line, limiter_len, 1)) != 0)
	{
		write_here_doc(line, exec, fd);
		here_doc_loop(&line, exec);
		if (signals_check(line, &fd, exec) == 1)
			return (fd);
	}
	close(fd);
	fd = open(DOC_NAME, INFILE_DOC, 0666);
	if (fd < 0)
		return (free(line), unlink(DOC_NAME), error(E_OPEN, exec));
	return (free(line), unlink(DOC_NAME), fd);
}

static void	here_doc_loop(char **line, t_exec *exec)
{
	set_here_doc_signal();
	ft_putstr_fd("> ", exec->stdout_fd);
	free(*line);
	*line = get_next_line_bonus(0);
}

/*
//REVIEW - write_here_doc

		This function takes as parameter a line of input from here_doc and
		its file descriptor.
		It writes the line on the here_doc fd, expanding environment variables.

//		1)	Iterate through the line until the end;
		2)	If a $ is found, find the end of the variable name;
		3)	Save the current character and replace it with a null terminator;
		4)	Replace the variable name with its value from the environment.
			If not found, do nothing;
		5)	Restore the character;
		6)	Write the line to the file descriptor.

*/
void	write_here_doc(char *line, t_exec *exec, int fd)
{
	int		i;
	int		end;
	char	*env_str;
	char	temp;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			end = i + 1;
			while (!ft_strchr(" $\n", line[end]))
				++end;
			temp = line[end];
			line[end] = 0;
			env_str = get_env(*exec->env, line + i + 1);
			if (env_str)
				ft_putstr_fd(env_str, fd);
			line[end] = temp;
			i = end - 1;
		}
		else
			write(fd, &line[i], 1);
	}
}

static int	signals_check(char *line, int *fd, t_exec *exec)
{
	if (!isatty(0) || g_exit_code_sig_received == CTRL_C)
	{
		write(1, "\n", 1);
		close_and_reset(fd);
		unlink(DOC_NAME);
		dup2(exec->stdin_fd, 0);
		return (1);
	}
	if (!line || g_exit_code_sig_received == CTRL_D)
	{
		dup2(exec->stdin_fd, 0);
		bash_message(E_HEREDOC_CTRL_D, NULL);
		close_and_reset(fd);
		*fd = open(DOC_NAME, INFILE_DOC, 0666);
		unlink(DOC_NAME);
		if (*fd < 0)
			return (free(line), error(E_OPEN, exec));
		return (1);
	}
	return (0);
}
