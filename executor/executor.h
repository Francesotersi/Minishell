/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:43:01 by alerusso          #+#    #+#             */
/*   Updated: 2025/03/21 16:02:04 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../Ssj_libft/libft.h"

typedef struct s_executor
{
	char			*content;
	unsigned int	id;
	unsigned int	prior;
	unsigned int	type:4;
}t_exec;

enum e_types
{
	COMMAND = 0,
	ARGUMENT = 1,
	FILES = 2,
	RED_OUT = 3,
	RED_IN = 4,
	RED_O_APPEND = 5,
	HERE_DOC = 6,
	PIPE = 7,
	AND = 8,
	OR = 9,
	WILDCARD = 10,
};

#endif
