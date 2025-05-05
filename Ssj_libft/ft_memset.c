/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:56:20 by ftersill          #+#    #+#             */
/*   Updated: 2024/11/28 08:48:18 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned long	count;
	unsigned char	*a;

	count = 0;
	a = (unsigned char *)s;
	while (count < n)
	{
		a[count] = (unsigned char)c;
		count++;
	}
	return (s);
}

// int main(void)
// {
// 	char a[6];	
// 	printf("%s", (char *)ft_memset(a, 'A', 5));
// 	return(0);
// }