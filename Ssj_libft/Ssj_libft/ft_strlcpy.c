/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:40:25 by ftersill          #+#    #+#             */
/*   Updated: 2024/11/27 17:00:36 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *source, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (source[j] != '\0')
		j++;
	if (size == 0)
		return (j);
	while (source[i] != '\0' && i < size -1)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (j);
}

// int	main()
// {
// 	char a[100] = "zio caane";
// 	char b[] = "stupid ass bea";
// 	int i = 15;
// 	ft_strlcpy(a, b, i);
// 	printf("lunghezza sorgente %d\n", i);
// 	printf("destination %s", a);
// 	return(0);
// }