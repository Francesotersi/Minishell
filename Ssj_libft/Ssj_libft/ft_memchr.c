/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:08:36 by ftersill          #+#    #+#             */
/*   Updated: 2024/11/29 08:47:18 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*a;

	a = (const unsigned char *)s;
	while (n--)
	{
		if (*a == (unsigned char)c)
		{
			return ((void *)a);
		}
		a++;
	}
	return (NULL);
}

// int main()
// {
// 	char b[] = "E` L`ORA DELLO SBUSO";
// 	printf("%s", (char *)ft_memchr(b, 'T', 10000000));
// 	return(0);
// }