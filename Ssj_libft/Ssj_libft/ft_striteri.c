/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:41:47 by ftersill          #+#    #+#             */
/*   Updated: 2024/11/28 08:46:17 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// char to_upper(unsigned int index, char *c)
// {
//     (void)index;
// 	*c = (char)toupper((unsigned char)*c);
// 	return(*c);
// }

// int main()
// {
//     char str[] = "hello world";
//     ft_striteri(str, (void*)to_upper);
//     printf("Modified string: %s\n", str);

//     return 0;
// }