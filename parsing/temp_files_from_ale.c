/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_files_from_ale.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:26:07 by ftersill          #+#    #+#             */
/*   Updated: 2025/04/22 13:12:31 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*REVIEW - cut_string

//Cut a string from start to end (included).
	
Example:

string = "Hello world!"
start = 5
end = 5

string becomes: "Helloworld!\0"
*/
// char	*_cut_string(char *string, size_t start, size_t end)
// {
// 	unsigned int	temp;
// 	unsigned int	temp1;
// 	unsigned int	string_len;

// 	end++;
// 	if (!(string) || !(*string) || (start > end))
// 		return (NULL);
// 	string_len = 0;
// 	while (string[string_len])
// 		++string_len;
// 	temp = start;
// 	while ((start != end) && (string[start] != 0))
// 		string[start++] = 0;
// 	end = start;
// 	start = temp;
// 	temp = 0;
// 	temp1 = string_len;
// 	while (end != string_len--)
// 	{
// 		string[start + temp] = string[end + temp];
// 		++temp;
// 	}
// 	string[temp1 - (end - start)] = 0;
// 	return (string);
// }

/*REVIEW - _free_matrix
//  Safely free a 2D matrix, even if NULL.
    Always return NULL.
*/
void    *_free_matrix(char **matrix)
{
    int index;
    index = 0;
    if (!matrix)
        return (NULL);
    while (matrix[index])
    {
        if (matrix[index])
            free(matrix[index]);
        matrix[index] = NULL;
        ++index;
    }
    if (matrix)
        free(matrix);
    return (NULL);
}
/*REVIEW - _free_three_d_matrix
//  Safely free a 3D matrix, even if NULL.
    Always return NULL.
*/
void    *_free_three_d_matrix(char ***matrix)
{
    int index_one;
    int index_two;
    index_one = 0;
    if (!matrix)
        return (NULL);
    while (matrix[index_one])
    {
        index_two = 0;
        while (matrix[index_one][index_two])
        {
            free(matrix[index_one][index_two]);
            matrix[index_one][index_two] = NULL;
            ++index_two;
        }
        free(matrix[index_one]);
        matrix[index_one] = NULL;
        ++index_one;
    }
    free(matrix);
    return (NULL);
}

/*REVIEW - _sub_strlen
	Count until the char is in the charset.
	TWO MODES:

	INCL(0): Count until the char is INCLUDED in the charset.
	EXCL(1): Count until the char is NOT INCLUDED in the charset.
*/
int	_sub_strlen(char *s, char *charset, int mode)
{
	int	i;

	i = 0;
	if (mode == 0)
	{
		while (((s[i] != '\0')) && \
		(ft_strchr(charset, s[i])))
		{
			++i;
		}
	}
	else if (mode == 1)
	{
		while (((s[i] != '\0')) && \
		!(ft_strchr(charset, s[i])))
		{
			++i;
		}
	}
	return (i);
}

//NOTE -	TO USE THESE FUNCTION, YOU MUST USE cpy_env FIRST!!!
//			We need to copy the environment to heap first, and saving the
//			new environment, its size and its last element.
//			Execution part needs these three variables to work properly.
//
//
//NOTE - Usage: give the environment taken in main;
//				the address of a char** variable, for the copied environment; 
//				the address of an int variable, that will store the env size;
//				the address of an int variable, that will store env last elem.
/*
//REVIEW - cpy_env

//		Operations:
		1)	Finds the search string in the environment matrix, skipping '=';
		2)	Where, if not NULL, is set to i if env[i], otherwise to -1;
		3)	Returns env[i], that MUST NOT BE FREED.
*/
int	cpy_env(char **old_env, char ***new_env, int *env_size, int *last_env)
{
	int	i;

	if (!old_env)
		return (1);
	i = 0;
	while (old_env[i])
		++i;
	*new_env = ft_calloc(i + *env_size + 1, sizeof(char *));
	if (!*new_env)
		return (1);
	i = 0;
	while (old_env[i])
	{
		(*new_env)[i] = ft_strdup(old_env[i]);
		if (!(*new_env)[i])
		{
			*new_env = _free_matrix(*new_env);
			return (1);
		}
		++i;
	}
	if (*env_size == 0)
		*env_size = i;
	*last_env = i;
	return (0);
}

//REVIEW - ft_getenv
//
//      Operations:
// 1)  Finds the search string in the environment matrix, skipping '=';
// 2)  Where, if not NULL, is set to i if env[i], otherwise to -1;
// 3)  Returns env[i], that MUST NOT BE FREED.

char    *ft_getenv(char **env, char *search, int *where)
{
	int     search_len;
	int     item_len;
	int     i;

	i = 0;
	search_len = ft_strlen(search);
	while (env[i])
	{
		item_len = _sub_strlen(env[i], "=", 1);
		if (!ft_strncmp(search, env[i], search_len) && \
			!ft_strncmp(search, env[i], item_len))
			break ;
		++i;
	}
	if (where)
		*where = (i * (env[i] != NULL)) + (-1 * (env[i] == NULL));
	return (env[i]);
}

//NOTE - Returns the content of an item in the environment, if exist. 
//				give **environment (NOT ADDRESS);
//				the string to search; 
//				an optional int ptr. If not NULL, it will be given the
//				index of the env element, or -1 if not found.
//				You can safely pass it to NULL.
//NOTE - YOU MUST NOT FREE THE RETURNED STRING! It's env memory!!!
char	*get_env(char **env, char *search)
{
	char	*item;

	if (!env[0])
		return (NULL);
	item = ft_getenv(env, search, NULL);
	if (!item)
		return (NULL);
	while (*item && *item != '=')
		++item;
	if (!*item)
		return (NULL);
	++item;
	return (item);
}