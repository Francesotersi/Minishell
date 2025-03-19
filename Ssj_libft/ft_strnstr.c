/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       ::      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:57:56 by ftersill          #+#    #+#             */
/*   Updated: 2024/11/20 14:02:20 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little || !little[0])
		return ((char *) big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && little[j] && i + j < len \
									&& big [i + j] == little[j])
			j++;
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	char a[] = "lorem ipsum dolor sit amen";
// 	char b[] = "ipsumm";
// 	printf("%s", ft_strnstr(a, b, 30));
// 	return(0);
// }
