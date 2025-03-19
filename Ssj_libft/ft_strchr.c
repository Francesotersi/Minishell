/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:22:38 by ftersill          #+#    #+#             */
/*   Updated: 2024/11/27 16:34:28 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != c && *s != '\0')
		s++;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

// int main()
// {
// 	char a[] = "cacca";
// 	char b[] = "a";
// 	printf("%s", ft_strchr(a, *b));
// 	return(0);
// }