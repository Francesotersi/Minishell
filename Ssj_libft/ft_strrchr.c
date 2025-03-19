/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:02:26 by ftersill          #+#    #+#             */
/*   Updated: 2024/11/27 16:33:12 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*smell;

	smell = NULL;
	while (*s != '\0')
	{
		if (*s == c)
			smell = s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return ((char *) smell);
}

//  int main()
// {
// 	char a[] = "cacato";
// 	char b[] = "a";
// 	printf("%s", ft_strrchr(a, *b));
// 	return(0);
// }