/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:03:58 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/22 09:41:12 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static void	merge_one(t_token *token, int i, bool update_type);
static void	manage_subshell(t_token *token);
static void	sort_id(t_token *token);
static void	switch_tokens(t_token *token, int i, int j);

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
		4)	We restart the loop, to merge '(' and ')';
		5)	Lastly, sort the id of every token, and decrease in subshell the
			layer of the <() token.
*/
void	merge_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token[i].content)
	{
		if (token[i].type == RED_IN && token[i].prior != token[i + 1].prior)
		{
			token[i].type = RED_SUBSHELL;
			token[i].prior += 1;
		}
		else if (is_red_sign(token[i].type))
		{
			merge_one(token, i, 0);
		}
		i++;
	}
	i = 0;
	while (token[i].content)
	{
		if (token[i].content[0] == '(' || token[i].content[0] == ')')
			merge_one(token, i, 1);
		else
			++i;
	}
	return (manage_subshell(token), sort_id(token));
}

/*REVIEW - merge_one

//		1)	free the current content ('>');
		2)	We update ONLY the content;
		3)	For every other token after current token,
			we drag them one position behind.
*/
static void	merge_one(t_token *token, int i, bool update_type)
{
	int	j;

	free(token[i].content);
	token[i].content = NULL;
	token[i].content = token[i + 1].content;
	if (update_type)
	{
		token[i].type = token[i + 1].type;
		token[i].prior = token[i + 1].prior;
	}
	i++;
	j = i;
	while (token[i].content && token[++j].content)
	{
		switch_tokens(token, i, j);
		++i;
	}
	switch_tokens(token, i, j);
}

static void	manage_subshell(t_token *token)
{
	while (token->content)
	{
		if (token->type == RED_SUBSHELL)
			token->prior -= 1;
		++token;
	}
}

/*REVIEW - merge_one

		Every token is indexed with its position in the token array.
		This index is its ID.

//		We set:
		-	The ID of every token;
		-	The command number of every token.

		Doing this is tough because we have to manage subshells:

		cat <(ls) <(ls) -a -a file1.txt file2.txt && grep -v <(./a.out) string
		Content		type				cmd_num		prior
		//cat		command (0)			0			0
		//<(		RED_SUBSHELL(10)	0			0
		//ls		command (0)			1			1
		//<(		RED_SUBSHELL(10)	0			0
		//ls		command (0)			2			1
		//-a		argument (1)		0			0
		//-a		argument (1)		0			0
		//file1.txt	argument (1)		0			0
		//file2.txt	argument (1)		0			0
		//&&		operator (3)		0			0
		//grep		command (0)			3			0
		//-v		argument (1)		3			0
		...

		In short, to do this we start from 'cat' and we go on until
		the current layer is equal or lower than the current token's layer.
		So, we reach end of prompt.
		Then we do the same for the next command (ls), but it stop 
		immeadiately after the first token, because the layer is
		0, and the current token's layer is 1.
*/
static void	sort_id(t_token *token)
{
	int		i;
	int		cmd_num;
	int		current_layer;
	t_token	*curr_token;

	cmd_num = 0;
	while (token->content)
	{
		i = token->id;
		current_layer = token->prior;
		curr_token = token;
		while (token->content && current_layer <= token->prior)
		{
			token->cmd_num = cmd_num;
			token->id = i++;
			++token;
		}
		++cmd_num;
		token = curr_token;
		next_cmd_block(&token, current_layer, _NO);
		token += (token->content != NULL);
	}
	token->cmd_num = cmd_num;
	token->prior = -1;
	token->id = -1;
}

static void	switch_tokens(t_token *token, int i, int j)
{
	token[i].content = token[j].content;
	token[i].id = token[j].id;
	token[i].prior = token[j].prior;
	token[i].space_on_right = token[j].prior;
	token[i].t_quote = token[j].t_quote;
	token[i].type = token[j].type;
}
