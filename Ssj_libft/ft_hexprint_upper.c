/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexprint_upper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:02:16 by lparolis          #+#    #+#             */
/*   Updated: 2025/01/14 15:30:29 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hexlen(unsigned int nb)
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

int	ft_hexprint_upper(unsigned int nb)
{
	char			*base;
	char			*temp;
	int				i;
	unsigned int	result;

	result = nb;
	i = ft_hexlen(nb) - 1;
	temp = (char *)ft_calloc((i + 2), sizeof(char));
	if (!temp)
		return (0);
	base = "0123456789ABCDEF";
	if (nb == 0)
	{
		write(1, "0", 1);
		return (free(temp), 1);
	}
	while (i >= 0)
	{
		temp[i--] = base[nb % 16];
		nb /= 16;
	}
	ft_putstr_fd(temp, 1);
	free(temp);
	return (ft_hexlen(result));
}

// int main(void)
// {
// 	unsigned int test_values[] = {
// 		0,              // Caso base: 0
// 		1,              // Il numero più piccolo non-zero
// 		15,             // Caso limite: 0xF (15 in decimale)
// 		16,             // Caso limite: 0x10 (16 in decimale)
// 		255,            // Caso limite: 0xFF (255 in decimale)
// 		256,            // Caso limite: 0x100 (256 in decimale)
// 		4294967295,     // Il numero massimo per un unsigned int (0xFFFFFFFF)
// 		123456789,      // Un numero casuale grande
// 		0xABCDEF,       // Caso con un numero esadecimale noto
// 	};

// 	int num_tests = sizeof(test_values) / sizeof(test_values[0]);

// 	for (int i = 0; i < num_tests; i++)
// 	{
// 		unsigned int test_value = test_values[i];
// 		printf("Test case %d (Value: %u): ", i + 1, test_value);

// 		// Chiama la funzione e stampa il risultato
// 		int len = ft_hexprint_upper(test_value);

// 		// Stampa la lunghezza ritornata dalla funzione
// 		// (la funzione dovrebbe restituire il numero di caratteri stampati)
// 		printf("\nNumber of characters printed: %d\n\n", len);
// 	}

// 	return 0;
// }