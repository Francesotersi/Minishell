/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD:executor/utils/utils_heredoc.c
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
=======
/*   utils_2.c                                          :+:      :+:    :+:   */
>>>>>>> master:parsing/utils_2.c
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:executor/utils/utils_heredoc.c
/*   Created: 2025/04/30 17:00:25 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/01 12:53:06 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
=======
/*   Created: 2025/04/29 08:58:54 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/05 09:00:26 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	skip_single_quotes(char *str, int *i)
{
	(*i)++;
	while (str[(*i)] != '\0' && str[(*i)] != '\'')
		(*i)++;
	if (str[(*i)] == '\'')
		(*i)++;
}

>>>>>>> master:parsing/utils_2.c
