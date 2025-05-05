/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:39:40 by lparolis          #+#    #+#             */
/*   Updated: 2025/01/14 15:30:37 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printer(const char *str, va_list(arglist))
{
	int	orion_pax;

	orion_pax = 0;
	if (*(str + 1) == '%')
		orion_pax = ft_putchar_count_fd('%', 1);
	else if (*(str + 1) == 'c')
		orion_pax = ft_putchar_count_fd((char)va_arg(arglist, int), 1);
	else if (*(str + 1) == 's')
		orion_pax = ft_putstr_count_fd(va_arg(arglist, char *), 1);
	else if (*(str + 1) == 'p')
		orion_pax = ft_putaddress_check(va_arg(arglist, unsigned long long));
	else if ((*(str + 1) == 'd') || (*(str + 1) == 'i'))
		orion_pax = ft_intcheck(va_arg(arglist, int), 1);
	else if (*(str + 1) == 'u')
		orion_pax = ft_unsigned_putnbr_fd(va_arg(arglist, unsigned int), 1);
	else if (*(str + 1) == 'x')
		orion_pax = ft_hexprint_lower(va_arg(arglist, unsigned int));
	else if (*(str + 1) == 'X')
		orion_pax = ft_hexprint_upper(va_arg(arglist, unsigned int));
	return (orion_pax);
}
