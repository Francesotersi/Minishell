/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:09:06 by ftersill          #+#    #+#             */
/*   Updated: 2024/11/28 10:44:11 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char			*a;
	const unsigned char		*b;
	size_t					count;

	a = (unsigned char *) dest;
	b = (const unsigned char *) src;
	count = 0;
	if (!dest && !src)
		return (NULL);
	while (count < n)
	{
		a[count] = b[count];
		count++;
	}
	return (dest);
}

// int	main()
// {
// 	char c[20] = "salvea  tutti";
// 	char d[] = "cacca pup";
// 	ft_memcpy(c, d, 3);
// 	printf("%s", c);
// 	return(0);
// }