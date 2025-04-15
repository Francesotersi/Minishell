/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:03:58 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/14 16:15:49 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	merge_one(t_token *token, int debug, int i);
static void	sort_id(t_token *token);

/*REVIEW - merge_tokens

//		Before launching execution for a command, we have to
		change a bit the token taken from parsing part:

		1)	We need a new type, RED_SUBSHELL, for <().
		This:	cat <(ls)
				Command		token		type			prior
				//cat		cat			command (0)		0
				//<			<			RED_IN	(4)		0
				//ls		ls			command (0)		1
		Becomes:
				Command		token		type			prior
				//cat		cat			command (0)		0
				//<			<			RED_SUBSHELL(10)0
				//ls		ls			command (0)		1
		
		2)	We need to shift all files in the same token of the
			redirector sign:
		This:	cat < file
				Command		token		type			prior
				//cat		cat			command (0)		0
				//<			<			RED_IN	(4)		0
				//file		file		files 	(2)		0
		Becomes:
				Command		token		type			prior
				//cat		cat			command (0)		0
				//<			file		RED_IN (4)

		In order to do this two changes:
		1)	We loop for all tokens;
		2)	If the token is <, and the next token has a different priority
			(so there is <(...)), mark the token as a RED_SUBSHELL;
		3)	Else, if is a regular redirector sign (<, <<, >, >>), merge it with
			its file;
		4)	Lastly, sort the id of every token.
*/
void	merge_tokens(t_token *token, int debug)
{
	int	i;

	i = 0;
	while (token[i].content)
	{
		if (token[i].type == RED_IN && token[i].prior != token[i + 1].prior)
		{
			token[i].type = RED_SUBSHELL;
		}
		else if (is_red_sign(token[i].type))
		{
			merge_one(token, debug, i);
		}
		i++;
	}
	sort_id(token);
}

/*REVIEW - merge_one

//		1)	If we are not in debug mode, free the current content ('>');
		2)	We update ONLY the content;
		3)	For every other token after current token,
			we drag them one position behind.
*/
static void	merge_one(t_token *token, int debug, int i)
{
	int	j;

	if (!debug)
		free(token[i].content);
	token[i].content = NULL;
	token[i].content = token[i + 1].content;
	i++;
	j = i;
	while (token[i].content && token[++j].content)
		token[i++] = token[j];
	token[i] = token[j];
}

/*REVIEW - merge_one

//		Every token is indexed with its position in the token array.
		This index is its ID.
*/
static void	sort_id(t_token *token)
{
	int	i;

	i = 0;
	while (token[i].content)
	{
		token[i].id = i;
		++i;
	}
}
