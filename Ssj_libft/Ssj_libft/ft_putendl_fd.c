/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:58:26 by ftersill          #+#    #+#             */
/*   Updated: 2024/12/02 12:21:57 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
		if (s[i] == '\0')
			write(fd, "\n", 1);
	}
}

// int main(void)
// {
// 	// Apertura del file di test
// 	int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		perror("Errore nell'aprire il file");
// 		return 1;
// 	}

// 	// Test con stringa vuota
// 	ft_putendl_fd("", fd);
// 	write(fd, "\n", 1);  // Separatore per leggibilità

// 	// Test con stringa normale
// 	ft_putendl_fd("Hello, World!", fd);
// 	write(fd, "\n", 1);

// 	// Test con stringa contenente caratteri speciali
// 	ft_putendl_fd("Line with newline\nand tab\tcharacters.", fd);
// 	write(fd, "\n", 1);

// 	// Test con stringa lunga
// 	ft_putendl_fd("This is a very long string to test how the.", fd);
// 	write(fd, "\n", 1);

// 	// Chiudere il file
// 	close(fd);

// 	return 0;
// }