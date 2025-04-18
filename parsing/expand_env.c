/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:55:30 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/18 11:55:36 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//				casi in cui non si espande la variabile
//	1)la variabile e` contenuta all`interno di quotes singole
//	2)


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
	token->content = (char*)ft_calloc(ft_strlen(temp) + e_l + 1, sizeof(char));
	if (!temp)
		return ;
	while (j < (*i))
		token->content[k++] = temp[j++];
	if (temp[j] == '$' && temp[j + 1] == '?')
	{
		j = 0;
		while (j < (e_l))
			token->content[k++] = exit_code[j++];
		(*i) += 1; 
	}
	j = (*i) + 1;
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

void	skip_single_quotes(char *str, int *i)
{
	(*i)++;
	while (str[(*i)] != '\0' && str[(*i)] != '\'')
		(*i)++;
	if (str[(*i)] == '\'')
		(*i)++;
}

void	expand_exit_code(t_token *token, t_data *gen)
{
	int		id;
	int		i;
	char	*exit_code;

	id = -1;
	i = 0;
	exit_code = NULL;
	while (token[++id].content != NULL)
	{
		i = 0;
		while (token[id].content[i] != '\0')
		{
			if (token[id].content[i] == '\'')
				skip_single_quotes(token[id].content, &i);
			else if (token[id].content[i] == '\"')
				expand_exit_code_2(&token[id], gen, &i, exit_code);
			else if (token[id].content[i] == '$' && token[id].content[i + 1] == '?')
				expand_exit_code_2(&token[id], gen, &i, exit_code);
			else
				i++;
		}
	}
}













// returns the string that has to be searched inside the env
char	*what_to_search(t_token *token, int *i)
{
	int		j;
	int		k;
	char	*to_search;

	to_search = NULL;
	(*i)++;
	k = (*i);
	j = 0;
	while (token->content[k] && token->content[k] != '$' && \
	token->content[k] != ' ' && token->content[k] != '\'' && \
	token->content[k] != '\"')
		k++;
	to_search = (char*)ft_calloc(k, sizeof(char));
	if (!to_search)
		return (NULL);
	while (token->content[(*i)] && token->content[(*i)] != '$' && \
	token->content[(*i)] != ' ' && token->content[(*i)] != '\'' && \
	token->content[(*i)] != '\"' && j < k)
	{
		to_search[j++] = token->content[(*i)++];
	}
	return (to_search);
}

// tok = token norminette is a piece of shit
void	expand_var(t_token *tok, int *i ,t_data *gen, char *search)
{
	char	*temp;

	(void)gen, (void)search;
	temp = NULL;
	if (tok->content[(*i)] == '\"')
	{
		while (tok->content[++(*i)] && tok->content[(*i)] != '\"')
		{
			if (tok->content[(*i)] && tok->content[(*i)] == '$' && \
			tok->content[(*i) + 1] != '\"' && tok->content[(*i) + 1] != '\'' \
			&& tok->content[(*i) + 1] != ' ')
			{
				temp = what_to_search(tok, i);
				printf("||%s||", temp);
				// search = search_in_env(gen->env);
			}
		}
		// (*i)++; // forse da rimuovere
	}
	else if (tok->content[(*i)] == '$' && tok->content[(*i) + 1] && \
	tok->content[(*i) + 1] != '\"' && tok->content[(*i) + 1] != '\'' \
	&& tok->content[(*i) + 1] != ' ')
	{
		temp = what_to_search(tok, i); //da fare free
		printf("||%s||", temp);
		
	}
}

void	expand_env(t_token *token, t_data *gen)
{
	int		id;
	int		i;
	char	*search;

	search = NULL;
	id = -1;
	i = 0;
	while (token[++id].content != NULL)
	{
		i = 0;
		while (token[id].content[i] != '\0')
		{
			if (token[id].content[i] == '\'')
				skip_single_quotes(token[id].content, &i);
			else if (token[id].content[i] == '\"')
				expand_var(&token[id], &i, gen, search);
			else if (token[id].content[i] == '$')
				expand_var(&token[id], &i, gen, search);
			else
				i++;
		}
	}
}

//	funzione chiamata all`interno della funzione remove_quotes_token()
//	nel file remove_quotes.c
//	--serve per espandere le variabili di ambiente all`interno della struttura
void	expanding_variables(t_token *token, t_data *gen)
{
	int	id;
	int	i;
	int var_id;

	id = 0;
	i = 0;
	var_id = 1;
	gen->exit_code = 100;
	expand_exit_code(token, gen);
	expand_env(token, gen);
}
