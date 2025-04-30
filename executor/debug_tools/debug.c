/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:08:08 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/28 19:47:25 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
# include "debug_resources/all.h"
# include "../executor.h"
# include <errno.h>

int	testing(int test_num, int fd, t_debug_data *deb);
int	alloc_memory_for_test(char *test, char ****matrix, t_token **exec, \
	t_debug_data *deb);
int	read_tokens(char ***matrix, t_token *exec, int line_num);
int	start_test_session(t_token *exec, t_debug_data *deb);

int	main(int argc, char **argv, char **env)
{
	int					fd;
	static char			*filename;
	static int			i = 0;
	static t_debug_data	deb;

	if (argc != 2 || argv[1][0] == '\0')
		return (fd_printf(2, "\nInsert a file num.\n"));
	if (getenv("CODESPACES"))
		filename = ft_strjoin(CODESPACE_DEBUG_PATH, argv[1]);
	else
		filename = ft_strjoin(PCHOME_DEBUG_PATH, argv[1]);
	fd = open(filename, O_RDWR, 0666);
	if (fd == -1 || !filename)
		return (l_printf("Err: |%s|", filename), free(filename), close(fd), 1);
	cpy_env(env, &deb.env, &deb.env_size, &deb.last_env);
	give_filedata(fd, filename);
	while ("LOOP: while there are tests to do")
	{
		deb.filename2 = filename;
		if (testing(i++, fd, &deb) != 0)
			break ;
		l_printf("\n\033[1;33mStop.\033[0m\n");
	}
	return (del_filedata(), free(filename), free_matrix(deb.env), 0);
}

int	testing(int test_num, int fd, t_debug_data *deb)
{
	char	***matrix;
	char	*test;
	char	*temp;
	int		num;
	t_token	*exec;

	temp = ft_itoa(test_num);
	test = ft_strjoin("[Test", temp);
	free(temp);
	if (!test)
		return (1);
	num = num_line(1, test);
	free(test);
	test = get_n_line(fd, num);
	if (!test)
		return (2);
	deb->temp = test;
	if (alloc_memory_for_test(test, &matrix, &exec, deb) != 0)
		return (free_three_d_matrix(matrix), free(test), free(exec), 3);
	if (read_tokens(matrix, exec, num + 1) != 0)
		return (free_three_d_matrix(matrix), free(test), free(exec), 4);
	if (start_test_session(exec, deb) != 0)
		return (free_three_d_matrix(matrix), free(test), free(exec), 5);
	return (free_three_d_matrix(matrix), free(test), free(exec), 0);
}

int	alloc_memory_for_test(char *test, char ****matrix, t_token **exec, \
	t_debug_data *deb)
{
	int	tokens;

	*exec = NULL;
	*matrix = NULL;
	while (!ft_strchr("\n,", *test))
		++test;
	while (!ft_strchr("\n0123456789", *test))
		++test;
	if (ft_strchr("\n", *test))
		return (3);
	tokens = ft_atoi(test);
	if (tokens <= 0)
		return (4);
	*matrix = (char ***)ft_calloc(tokens + 1, sizeof(char **));
	if (!(*matrix))
		return (1);
	*exec = (t_token *)ft_calloc(tokens + 1, sizeof(t_token));
	if (!(*exec))
		return (1);
	deb->matrix = *matrix;
	deb->tokens = *exec;
	return (get_filedata(&deb->fd_to_close, &deb->filename1), 0);
}

int	read_tokens(char ***matrix, t_token *exec, int line_num)
{
	int		token_num;

	token_num = 0;
	while ("LOOP: I loop until I have found all tokens!")
	{
		matrix[token_num] = read_all_line(line_num + token_num);
		if (!matrix[token_num])
			break ;
		exec[token_num].id = token_num;
		exec[token_num].content = matrix[token_num][0];
		exec[token_num].type = ft_atoi(matrix[token_num][1]);
		exec[token_num].prior = ft_atoi(matrix[token_num][2]);
		++token_num;
	}
	if (matrix[0] == NULL)
		return (1);
	return (0);
}

int	start_test_session(t_token *exec, t_debug_data *deb)
{
	t_token	*head;

	head = exec;
	l_printf("\n[START]\n++++++++++++++++++++\n");
	while (exec->content)
	{
		l_printf("\n+------------------+\nToken %d:\n", exec->id);
		l_printf("Content:\t|%s|\n", exec->content);
		l_printf("Id:\t\t|%d|\n", exec->id);
		l_printf("Type:\t\t|%d|\n", exec->type);
		l_printf("Priority:\t|%d|\n", exec->prior);
		++exec;
	}
	l_printf("\n+------------------+\n[END]\n++++++++++++++++++++\n");
	l_printf("\nTest for: ");
	exec = head;
	while (exec->content)
	{
		l_printf("%s ", exec->content);
		++exec;
	}
	exec = head;
	l_printf("\n\033[1;32mExecution:\033[0m\n");
	execute(exec, (void *)deb, _YES);
	return (l_printf("\n\033[1;33mExit code:\033[0m %d", deb->exit_status));
}
