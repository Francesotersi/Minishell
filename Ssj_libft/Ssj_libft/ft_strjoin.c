/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:53:33 by ftersill          #+#    #+#             */
/*   Updated: 2024/11/28 14:42:54 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rts;
	size_t	mel;
	size_t	nel;

	rts = (char *)malloc((sizeof(char)) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	mel = 0;
	nel = 0;
	if (!rts)
		return (NULL);
	while (s1[mel] != '\0')
	{
		rts[mel] = s1[mel];
		mel++;
	}
	while (s2[nel] != '\0')
	{
		rts[mel] = s2[nel];
		mel++;
		nel++;
	}
	rts[mel] = '\0';
	return (rts);
}

// int main()
// {
// 	char *a = "buttata ";
// 	char *b = "di fuori";
// 	printf("%s", ft_strjoin(a, b));
// 	return(0);
// }
