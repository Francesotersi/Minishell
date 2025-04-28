/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:55:30 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/28 11:58:28 by ftersill         ###   ########.fr       */
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
	int		u;

	to_search = NULL;
	k = (*i) + 1;
	j = 0;
	while (token->content[k] && token->content[k] != '$' && \
	token->content[k] != ' ' && token->content[k] != '\'' && \
	token->content[k] != '\"')
		k++;
	to_search = (char*)ft_calloc(k, sizeof(char));
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

void	insert_var_env(char *search, t_token *token, int *i, char *temp)
{
	char	*dup;
	int		k;
	int		j;
	
	k = 0;
	j = 0;
	// ricordati che se get_env ritorna NULL te la variabile da espandere la devi COMPLETAMENTE saltare
	dup = ft_strdup(token->content);
	free(token->content);
	token->content = (char*)ft_calloc(ft_strlen(dup) + ft_strlen(temp) + \
		ft_strlen(search) + 1, sizeof(char));
	if (!token->content)
		return /* MALLOC ERROR */;
	while (j < (*i))
		token->content[k++] = dup[j++];
	if (dup[j] == '$' && dup[j] != '\0')
	{
		j = 0;
		while (j < (int)ft_strlen(search))
			token->content[k++] = search[j++];
	}
	j = (*i) + ft_strlen(temp) + 1;
	while (dup[j] != '\0')
		token->content[k++] = dup[j++];
	free(dup);
}

// CHIEDERE AL FHURER ALERUSSO SE LA GESTIONE DEI DELLARI SINGOLI DEVE ESSERE GESTITA

void	skip_env_var(t_token *token, int *i, char *temp)
{
	int		k;
	int		j;
	int		temp_len;
	char	*dup;
	
	dup = ft_strdup(token->content);
	free(token->content);
	token->content = (char*)ft_calloc(ft_strlen(dup) + 1, sizeof(char));
	if (!token->content)
		return /* malloc error */;
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

// tok = token, norminette is a piece of shit echo '$HOME'"$HOME'$HOME'"
void	expand_var(t_token *tok, int *i ,t_data *gen, char *search)
{
	char	*temp;

	temp = NULL;
	if (tok->content[(*i)] == '\"')
	{
		(*i)++;
		while (tok->content[(*i)] && tok->content[(*i)] != '\"')
		{
			if (tok->content[(*i)] && tok->content[(*i)] == '$' && \
			tok->content[(*i) + 1] != '\"' && tok->content[(*i) + 1] != '\'' \
			&& tok->content[(*i) + 1] != ' ')
			{
				temp = what_to_search(tok, i); //da fare free
				search = get_env(gen->env, temp);
				if (search)
					insert_var_env(search, tok, i, temp);
				else
					skip_env_var(tok, i, temp);
			}
			else
				(*i)++;
		}
		(*i)++;
	}
	else if (tok->content[(*i)] == '$' && tok->content[(*i) + 1] && \
	tok->content[(*i) + 1] != '\"' && tok->content[(*i) + 1] != '\'' \
	&& tok->content[(*i) + 1] != ' ')
	{
		temp = what_to_search(tok, i); //da fare free
		search = get_env(gen->env, temp);
		if (search)
			insert_var_env(search, tok, i, temp);
		else
			skip_env_var(tok, i, temp);
	}
	else
		(*i)++;
	free(temp);
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
	expand_exit_code(token, gen);
	expand_env(token, gen);
}
