/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:10:30 by alerusso          #+#    #+#             */
/*   Updated: 2025/03/25 16:58:12 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*REVIEW - 
	is_redirector_sign searches for:	
										{>}
										{<}
										{>>}
										{<<}
*/
int	is_red_sign(int sign)
{
	if (sign == RED_OUT)
		return (YES);
	else if (sign == RED_IN)
		return (YES);
	else if (sign == RED_O_APPEND)
		return (YES);
	else if (sign == HERE_DOC)
		return (YES);
	return (NO);
}

/*REVIEW - 
	is_execution_separator searches for:	
											{|}
											{&&}
											{||}
*/
int	is_exec_sep(int sign)
{
	if (sign == PIPE)
		return (YES);
	else if (sign == AND)
		return (YES);
	else if (sign == OR)
		return (YES);
	return (NO);
}
