/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:58:54 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/08 09:20:47 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_error(char *str, int exit_c, t_data *gen, char *token)
{
	printf("bash: %s %s\n", str, token);
	gen->exit_code = exit_c;
}

void	skip_single_quotes(char *str, int *i)
{
	(*i)++;
	while (str[(*i)] != '\0' && str[(*i)] != '\'')
		(*i)++;
	if (str[(*i)] == '\'')
		(*i)++;
}
