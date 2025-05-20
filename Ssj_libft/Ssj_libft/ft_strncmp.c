/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:48:43 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/16 12:32:46 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	if (!s1 || !s2 || s1[0] == '\0')
		return (999999);
	while (i < n && s1[i] && (s1[i] == s2[i]))
		i++;
	if (i == n)
		return (0);
	return (a[i] - b[i]);
}

// int	main()
// {
// 	char	a[] = "ciaov";
// 	char	b[] = "cazozooaooada";
// 	int n = 2;
// 	printf("%d", ft_strncmp(a, b, n));
// 	return (0);
// } 