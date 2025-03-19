/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:23:26 by lparolis          #+#    #+#             */
/*   Updated: 2025/01/14 15:31:04 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void *xcalloc(size_t n, size_t x)
// {
// 	(void)n;
// 	(void)x;
// 	return NULL;
// }

int	ft_putaddress_check(unsigned long long nb)
{
	if (!nb)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	return (ft_putaddress(nb));
}

static int	ft_hexlen(unsigned long long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 16;
		len++;
	}
	return (len);
}

int	ft_putaddress(unsigned long long nb)
{
	int					i;
	char				*base;
	char				*temp;
	unsigned long long	result;

	result = nb;
	i = ft_hexlen(nb) - 1;
	temp = (char *)ft_calloc(i + 1, sizeof(char));
	if (!temp)
		return (0);
	base = "0123456789abcdef";
	if (nb == 0)
		return (write(1, "0", 1), free(temp), 1);
	while (i >= 0)
	{
		temp[i] = base[nb % 16];
		nb /= 16;
		i--;
	}
	write(1, "0x", 2);
	write(1, temp, ft_hexlen(result));
	free(temp);
	return (2 + ft_hexlen(result));
}

// int main(void)
// {
// 	void *test_values[] = {
// 		0,                   // Caso base: 0
// 		1,                   // Il numero più piccolo non-zero
// 		15,                  // Caso limite: 0xF (15 in decimale)
// 		16,                  // Caso limite: 0x10 (16 in decimale)
// 		255,                 // Caso limite: 0xFF (255 in decimale)
// 		256,                 // Caso limite: 0x100 (256 in decimale)
// 		4294967295,          // Il numero max per un unsigned int (0xFFFFFFFF)
// 		123456789012345678,  // Un numero casuale molto grande
// 		0xABCDEF,            // Un numero esadecimale noto
// 	};

// 	int num_tests = sizeof(test_values) / sizeof(test_values[0]);

// 	for (int i = 0; i < num_tests; i++)
// 	{
// 		void *test_value = test_values[i];
// 		printf("Test case %d \n(Value: %p): ", i + 1, test_value);

// 		// Chiama la funzione e stampa il risultato
// 		ft_putaddress(test_value);
// 		//printf ("\norigin : |%p|\n", test_value);

// 		// Stampa la lunghezza ritornata dalla funzione
// 		// (la funzione dovrebbe restituire il numero di caratteri stampati)
// 		//printf("\nNumber of characters printed: %d\n\n", len);
// 	}

// 	return 0;
// }
