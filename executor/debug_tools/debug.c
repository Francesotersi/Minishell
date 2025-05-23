/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:08:08 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/15 16:46:17 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "debug_resources/all.h"
#include "../executor.h"
#include <errno.h>

int	testing(int test_num, int fd, t_debug_data *deb);
int	alloc_memory_for_test(char *test, char ****matrix, t_token **exec, \
	t_debug_data *deb);
int	read_tokens(char ***matrix, t_token *exec, int line_num);
int	start_test_session(t_token *exec, t_debug_data *deb);

int	main(int argc, char **argv, char **env)
{
	int					fd;
	static int			i = 0;
	static t_debug_data	deb;

	if (argc != 2 || argv[1][0] == '\0')
		return (fd_printf(2, "\nInsert a file num.\n"));
	if (getenv("CODESPACES"))
		deb.filename2 = ft_strjoin(CODESPACE_DEBUG_PATH, argv[1]);
	else if (ft_strncmp(getenv("HOME"), "/nfs/homes/alerusso", 22) == 0)
		deb.filename2 = ft_strjoin(SCHOOL_DEBUG_PATH, argv[1]);
	else
		deb.filename2 = ft_strjoin(PCHOME_DEBUG_PATH, argv[1]);
	fd = open(deb.filename2, O_RDWR, 0666);
	if (fd == -1 || !deb.filename2)
		return (l_printf("Err: |%s|", deb.filename2), \
		free(deb.filename2), close(fd), 1);
	cpy_env(env, &deb.env, &deb.env_size, &deb.last_env);
	give_filedata(fd, deb.filename2);
	while ("LOOP: while there are tests to do")
	{
		if (testing(i++, fd, &deb) != 0)
			break ;
		l_printf("\n\033[1;33mStop.\033[0m\n");
	}
	return (del_filedata(), free(deb.filename2), free_matrix(deb.env), 0);
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
	return (execute(exec, (void *)deb, _YES));
}
