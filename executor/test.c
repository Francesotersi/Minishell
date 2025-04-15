/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:16:00 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/12 18:35:19 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

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
