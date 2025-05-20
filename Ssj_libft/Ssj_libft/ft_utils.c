/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 09:36:05 by lparolis          #+#    #+#             */
/*   Updated: 2025/01/14 15:30:04 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_count_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr_count_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_numlen(int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
	{
		return (1);
	}
	if (nb < 0)
	{
		len++;
	}
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

int	ft_unsigned_numlen(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

/* int main()
{
	// Test ft_putchar_count_fd
	char ch = 'A';
	printf("Test ft_putchar_count_fd:\n");
	int written = ft_putchar_count_fd(ch, 1);
	printf("\nCarattere scritto: %c, num carat scritti: %d\n", ch, written);

	// Test ft_putstr_count_fd
	char *str = "Hello, world!";
	printf("\nTest ft_putstr_count_fd:\n");
	int str_length = ft_putstr_count_fd(str, 1);
	printf("\nNumero di caratteri scritti: %d\n", str_length);

	// Caso stringa NULL
	char *null_str = NULL;
	int null_str_length = ft_putstr_count_fd(null_str, 1);
	printf("\nTest con str NULL, num carat scritti: %d\n", null_str_length);

	// Test ft_numlen
	int num = -12345;
	printf("\nTest ft_numlen:\n");
	int num_len = ft_numlen(num);
	printf("Lunghezza del numero %d: %d\n", num, num_len);

	// Test con INT_MIN
	int min_num = -2147483647;
	printf("\nTest ft_numlen con INT_MIN:\n");
	int min_num_len = ft_numlen(min_num);
	printf("Lunghezza di INT_MIN: %d\n", min_num_len);

	// Test con INT_MAX
	int max_num = 2147483647;
	printf("\nTest ft_numlen con INT_MAX:\n");
	int max_num_len = ft_numlen(max_num);
	printf("Lunghezza di INT_MAX: %d\n", max_num_len);

	// Test con 0
	int zero_num = 0;
	printf("\nTest ft_numlen con 0:\n");
	int zero_num_len = ft_numlen(zero_num);
	printf("Lunghezza di 0: %d\n", zero_num_len);

	// Test ft_unsigned_numlen
	unsigned int unsigned_num = 98765;
	printf("\nTest ft_unsigned_numlen:\n");
	int unsigned_num_len = ft_unsigned_numlen(unsigned_num);
	printf("Lungh del num unsigned %u: %d\n", unsigned_num, unsigned_num_len);

	// Test con UINT_MAX
	unsigned int max_unsigned_num = 4294967295;
	printf("\nTest ft_unsigned_numlen con UINT_MAX:\n");
	int max_unsigned_num_len = ft_unsigned_numlen(max_unsigned_num);
	printf("Lunghezza di UINT_MAX: %d\n", max_unsigned_num_len);

	// Test con 0 (unsigned)
	unsigned int zero_unsigned_num = 0;
	printf("\nTest ft_unsigned_numlen con 0 (unsigned):\n");
	int zero_unsigned_num_len = ft_unsigned_numlen(zero_unsigned_num);
	printf("Lunghezza di 0 (unsigned): %d\n", zero_unsigned_num_len);

	return 0;
} */