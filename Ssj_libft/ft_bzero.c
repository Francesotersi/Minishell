/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 08:36:42 by ftersill          #+#    #+#             */
/*   Updated: 2024/11/28 08:52:19 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			count;
	unsigned char	*a;

	count = 0;
	a = (unsigned char *) s;
	while (count < n)
	{
		a[count] = 0;
		count++;
	}
}

// int main()
// {
// 	char b[5];
// 	ft_bzero(b, 5);
// 	printf("%s", b);
// 	return(0);
// }