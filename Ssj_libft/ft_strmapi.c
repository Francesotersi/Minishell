/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:23:18 by ftersill          #+#    #+#             */
/*   Updated: 2024/12/03 17:07:43 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*rts;
	size_t	i;
	size_t	count;

	i = 0;
	count = ft_strlen(s);
	if (!s)
		return (NULL);
	rts = (char *)malloc(sizeof(char) * (count + 1));
	if (!s)
		return (NULL);
	while (i < count)
	{
		rts[i] = f(i, s[i]);
		i++;
	}
	rts[i] = '\0';
	return (rts);
}

// static char to_uppercase(unsigned int index, char c)
// {
// 	(void)index;
//     if (c >= 'a' && c <= 'z')
//         return c - 'a' + 'A';
//     return c;
// }

// int main()
// {
// 	char *cac = "override this !";
// 	printf("%s", ft_strmapi(cac, *to_uppercase));
// 	return(0);
// }