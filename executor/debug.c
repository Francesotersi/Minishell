/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:08:08 by ftersill          #+#    #+#             */
/*   Updated: 2025/03/19 17:02:06 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "debug.h"

int	main(void)
{
	int		fd;
	char	**matrix;

	fd = open("debug_resources/input_samples/1", O_CREAT | O_RDWR, 0666);
	if (fd == -1)
		return (l_printf("Failed to open file"));
	matrix = ft_split("\tContent1,\tSeparator,\tContent2,\tPunti_ferita,\
	\tRayquaza,\tNumero_di_peni_preso", ',');
	initiate_file(fd, "debug_resources/input_samples/1", matrix);
}
