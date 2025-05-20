/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:20:38 by ftersill          #+#    #+#             */
/*   Updated: 2024/11/28 09:06:33 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char	prin;

	if (nb >= 10 || nb <= -10)
		ft_putnbr_fd(nb / 10, fd);
	else
	{
		if (nb < 0)
			write(fd, "-", 1);
	}
	if (nb < 0)
		prin = ((nb % 10) * -1) + '0';
	else
		prin = (nb % 10) + '0';
	write(fd, &prin, 1);
}

// int main()
// {
// 	ft_putnbr_fd(69, 1);
// 	return(0);
// }