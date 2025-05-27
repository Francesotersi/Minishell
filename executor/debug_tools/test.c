/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:16:00 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/15 16:45:35 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>

//SECTION - Opening multiple fds on the same file
//NOTE - 	Test OK!
/*
int	main()
{
	static int	fds[30];
	int			i;

	i = 0;
	while (i != 8)
	{
		fds[i] = open("execute.c", O_RDONLY);
		if (fds[i] == -1)
			return (printf("gay"));
		i++;
	}
	i = 0;
	while (fds[i])
		printf("\nfd %d", fds[i++]);
	return (printf("\nEtero"));
}
*/
//SECTION - Address of the same strings in different process
//NOTE - 	Test OK! Same addresses
/*
int	main()
{
	char	*s = calloc(15, 1);
	strcpy(s, "Test");
	char	**ptr;
	pid_t	pid;

	ptr = &s;
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		printf("Ptr for string %s:\t%p. Address: %p\n", s, s, &s);
		printf("ptr for string %s:\t%p. Address: %p\n", *ptr, *ptr, ptr);
	}
}*/
//SECTION - The environ global variable
//NOTE - 	Test OK! But useless
/*
int	main(void)
{
	int			i;
	extern char	**environ;	

	i = 0;
	printf("\n\033[33mEnv:\033[0m\n");
	while (environ[i])
	{
		printf("\t%s\n", environ[i]);
		++i;
	}
	unsetenv("USER");
	printf("\n\n\033[31mUnsetted user...\033[0m\n\n");
	i = 0;
	while (environ[i])
	{
		printf("\t%s\n", environ[i]);
		++i;
	}
	setenv("USER", "new user", 1);
	printf("\n\n\033[32mAdded user...\033[0m\n");
	i = 0;
	while (environ[i])
	{
		printf("\t%s\n", environ[i]);
		++i;
	}
}*/
//SECTION - Opening a file, closing it then using its fd
//NOTE - 	Test OK! you can do it. Files are saved
/*
int	main()
{
	char	line[12];

	int	fd = open("a.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	write(fd, "Broly\n", 6);
	close(fd);
	fd = open("a.txt", O_RDWR | O_CREAT, 0666);
	read(fd, line, 1);
	unlink("a.txt");
	read(fd, line + 1, 4);
	line[5] = 0;
	write(1, line, 5);
}
*/

//SECTION - cd e getcwd gestiscono da soli i casi limite?
//NOTE - 	Test OK!
/*
int	main(void)
{
	int		len;
	char	*pwd;
	int		exit_status;

	exit_status = chdir("///././bin/././");
	if (exit_status == -1)
		return (printf("sono un fallito che gioca a fortnite"));
	pwd = getcwd(NULL, 0);
	free(pwd);
	pwd = getcwd(NULL, 0);
	printf("EXIT STATUS: %d;\nbash:%s\n", exit_status, pwd);
	free(pwd);
}
*/
/*
static void	to_free(char *s1, char *s2, int which);
#include "debug_resources/all.h"
char	*_cat_string(char *src, char *catstr, size_t start, int which_free)
{
	size_t	i;
	char	*new;
	size_t	catstr_len;

	if (!src || !catstr)
		return (to_free(src, catstr, which_free), NULL);
	i = 0;
	while (src[i] && i < start)
		++i;
	if (i > start && !src[i])
		return (to_free(src, catstr, which_free), NULL);
	catstr_len = ft_strlen(catstr);
	new = (char *)ft_calloc(ft_strlen(src) + catstr_len + 2, sizeof(char));
	if (new)
	{
		ft_strlcpy(new, src, start + 2);
		ft_strlcpy(new + start, catstr, catstr_len + 2);
		if (source[i])
			sub_strcpy(new + start + catstr_len, src + start, "", EXCLUDE);
	}
	return (to_free(src, catstr, which_free), new);
}

static void	to_free(char *s1, char *s2, int which)
{
	if (which == 1 || which >= 3)
		free(source);
	if (which == 2 || which >= 3)
		free(catstr);
}

int	main()
{
	char	*test1 = "AAA";
	char	*sub = "AAA";
	char	*new;
	int		len = 2;

	new = _cat_string(test1, sub, len, 0);
	fd_printf(1, "%s\n", new);
	free(new);
}*/

/*
//SECTION - Cosa torna wait?
//NOTE - Wait torna l'ultimo figlio che CRONOLOGICAMENTE è finito
int	main()
{
	pid_t	pid[50];
	int		count;
	int		exit_status;

	count = 0;
	while (count != 40)
	{
		pid[count] = fork();
		if (pid[count] < 0)
			return (printf("vaffanculo"));
		else if (pid[count] == 0)
		{
			if (count % 2 == 0)
				sleep(1);
			exit(count);
		}
		++count;
	}
	while (wait(&exit_status) > 0)
		printf("%d\n", exit_status / 256);
	return (0);
}*/

/*
//SECTION - Dove vanno gli fd aperti con pipe?
//NOTE - A quanto sembra vanno in /dev/fd/
int	main()
{
	int 			fds[2];
	DIR				*dir;
	struct dirent	*file;

	dir = opendir("/dev/fd");
	file = readdir(dir);
	while (file)
	{
		printf("%s\n", file->d_name);
		file = readdir(dir);
	}
	pipe(fds);
	closedir(dir);
	printf("\nIN:\t%d\nOUT:\t%d\n", fds[0], fds[1]);
	dir = opendir("/dev/fd");
	file = readdir(dir);
	while (file)
	{
		printf("%s\n", file->d_name);
		file = readdir(dir);
	}
	closedir(dir);
	close(fds[0]);
	close(fds[1]);
}*/

//SECTION - Main per testare le wildcards
/*
cc test.c ../bonus/bonus_wildcards1.c ../bonus/bonus_wildcards2.c \
../utils/general3.c ../utils/general.c ../utils/general4.c \
../utils/printf_fd.c \
../env_management/environment.c ../env_management/environment2.c \
debug_resources/libft.a -g -Wall -Wextra -Werror
*/
/*
#include "../executor.h"

int	main()
{
	char	*test1 = "*";
	char	*test2 = "bu*pwd*.c";
	char	*test3 = "/bin/";//add * after /
	char	*result;

	if (convert_wildcard(test1, &result))
		return (printf("ERROR!!!"));
	printf("\nRESULT FOR %s:\n|%s|\n", test1, result);
	free(result);
	if (convert_wildcard(test2, &result))
		return (printf("ERROR!!!"));
	printf("\nRESULT FOR %s:\n|%s|\n", test2, result);
	free(result);
	if (convert_wildcard(test3, &result))
		return (printf("ERROR!!!"));
	printf("\nRESULT FOR %s:\n|%s|\n", test3, result);
	free(result);
	printf("\n\nYou didn't crash!\n");
}*/

//SECTION - Divisione per impostare correttamente exit code
/*
int	main(void)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid < 0)
		return (printf("vaffanculo"));
	else if (pid == 0)
	{
		sleep(100);
		exit(0);
	}
	wait(&exit_status);
	printf("%d\n", exit_status / 256);
	return (0);
}*/
