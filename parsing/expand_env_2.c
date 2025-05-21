/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:17:14 by ftersill          #+#    #+#             */
/*   Updated: 2025/05/21 12:58:24 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// e_l = exit_code_len
void	insert_exit_code(t_token *token, int *i, int e_l, char *exit_code)
{
	char	*temp;
	int		j;
	int		k;

	j = 0;
	k = 0;
	temp = ft_strdup(token->content);
	free(token->content);
	e_l = ft_strlen(exit_code);
	token->content = (char *)ft_calloc(ft_strlen(temp) + e_l + 1, \
		sizeof(char));
	if (!temp)
		return ;
	while (j < (*i))
		token->content[k++] = temp[j++];
	if (temp[j] == '$' && temp[j + 1] == '?')
	{
		j = 0;
		while (j < (e_l))
			token->content[k++] = exit_code[j++];
	}
	j = (*i) + 2;
	while (temp[j] != '\0')
		token->content[k++] = temp[j++];
	free(temp);
}

void	expand_exit_code_2(t_token *token, t_data *gen, int *i,
	char *exit_code)
{
	int		exit_code_len;

	exit_code_len = 0;
	if (token->content[(*i)] == '\"')
	{
		while (token->content[++(*i)] && token->content[(*i)] != '\"')
		{
			if (token->content[(*i)] == '$' && token->content[(*i) + 1] == '?')
			{
				exit_code = ft_itoa(gen->exit_code);
				insert_exit_code(token, i, exit_code_len, exit_code);
				free(exit_code);
			}
		}
		(*i)++;
	}
	else if (token->content[(*i)] == '$' && token->content[(*i) + 1] == '?')
	{
		exit_code = ft_itoa(gen->exit_code);
		insert_exit_code(token, i, exit_code_len, exit_code);
		free(exit_code);
	}
}

void	expand_exit_code(t_token *token, t_data *gen, int *id, int *i)
{
	char	*exit_code;

	exit_code = NULL;
	if (token[(*id)].content[(*i)] == '\"')
		expand_exit_code_2(&token[(*id)], gen, i, exit_code);
	else if (token[(*id)].content[(*i)] == '$' && \
		token[(*id)].content[(*i) + 1] == '?')
		expand_exit_code_2(&token[(*id)], gen, i, exit_code);
	else
		(*i)++;
}

// returns the string that has to be searched inside the env
char	*what_to_search(t_token *token, int *i)
{
	int		j;
	int		k;
	char	*to_search;
	int		u;

	to_search = NULL;
	k = (*i) + 1;
	j = 0;
	while (token->content[k] && token->content[k] != '$' && \
	token->content[k] != ' ' && token->content[k] != '\'' && \
	token->content[k] != '\"')
		k++;
	to_search = (char *)ft_calloc(k, sizeof(char));
	if (!to_search)
		return (NULL);
	u = (*i) + 1;
	while (token->content[u] && token->content[u] != '$' && \
	token->content[u] != ' ' && token->content[u] != '\'' && \
	token->content[u] != '\"' && j < k)
	{
		to_search[j++] = token->content[u++];
	}
	return (to_search);
}

void	skip_env_var(t_token *token, int *i, char *temp)
{
	int		k;
	int		j;
	int		temp_len;
	char	*dup;

	dup = ft_strdup(token->content);
	free(token->content);
	token->content = (char *)ft_calloc(ft_strlen(dup) + 1, sizeof(char));
	if (!token->content)
		return ;
	temp_len = ft_strlen(temp);
	j = 0;
	k = 0;
	while (k < (*i))
		token->content[j++] = dup[k++];
	while (k <= ((*i) + temp_len))
		k++;
	while (dup[k])
		token->content[j++] = dup[k++];
	free(dup);
}
