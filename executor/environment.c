/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:26:15 by alerusso          #+#    #+#             */
/*   Updated: 2025/04/14 10:52:55 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
		return (E_NOENV);
	i = 0;
	while (old_env[i])
		++i;
	*new_env = ft_calloc(i + *env_size + 1, sizeof(char *));
	if (!*new_env)
		return (E_MALLOC);
	i = 0;
	while (old_env[i])
	{
		(*new_env)[i] = ft_strdup(old_env[i]);
		if (!(*new_env)[i])
		{
			*new_env = _free_matrix(*new_env);
			return (E_MALLOC);
		}
		++i;
	}
	if (*env_size == 0)
		*env_size = i;
	*last_env = i;
	return (0);
}

//NOTE - Returns the content of an item in the environment, if exist. 
//				give **environment (NOT ADDRESS);
//				the string to search; 
//				an optional int ptr. If not NULL, it will be given the
//				index of the env element, or -1 if not found.
//				You can safely pass it to NULL.
//NOTE - YOU MUST NOT FREE THE RETURNED STRING! It's env memory!!!

/*
//REVIEW - ft_getenv
//
//		Operations:
		1)	Finds the search string in the environment matrix, skipping '=';
		2)	Where, if not NULL, is set to i if env[i], otherwise to -1;
		3)	Returns env[i], that MUST NOT BE FREED.
*/
char	*ft_getenv(char **env, char *search, int *where)
{
	int		search_len;
	int		item_len;
	int		i;

	search_len = ft_strlen(search);
	i = 0;
	while (env[i])
	{
		item_len = _sub_strlen(env[i], "=", EXCL);
		if (!ft_strncmp(search, env[i], search_len) && \
		!ft_strncmp(search, env[i], item_len))
			break ;
		++i;
	}
	if (where)
		*where = (i * (env[i] != NULL)) + (-1 * (env[i] == NULL));
	return (env[i]);
}

//NOTE - 	Returns this stuff: "~/42projects/Minishell$"
//			Usage: give **environment (NOT ADDRESS), returns pwd location.
//NOTE - YOU MUST FREE THE RETURNED STRING!	If NULL is returned, is E_MALLOC!
/*
//REVIEW - get_pwd_address

//		Operations:
		1)	Get pwd and home from the environment;
		2)	If pwd does not exists, return the pwd from getcwd;
		3)	If pwd exists but home does not, return pwd + 4,
			because we skip the first four bytes (PWD=/user/homes/...);
		4)	If both pwd and home exists in env, 
			if pwd + 4 (/user/homes/...) is equal to home + 5 (we skip HOME=),
				we return pwd skipping home_len bytes, and putting "~/" behind;
			Else
				we return pwd + 4.
*/
char	*get_pwd_address(char **env)
{
	char	*pwd;
	char	*home;
	int		home_len;

	pwd = ft_getenv(env, "PWD", NULL);
	home = ft_getenv(env, "HOME", NULL);
	if (!pwd)
		return (getcwd(NULL, 0));
	else if (pwd && !home)
	{
		return (ft_strdup(pwd + 4));
	}
	else if (pwd && home)
	{
		home_len = ft_strlen(home);
		if (ft_strncmp(pwd + 4, home + 5, home_len - 5))
			return (ft_strdup(pwd + 4));
		return (_ft_strjoin_free(ft_strdup("~/"), ft_strdup(pwd + home_len)));
	}
	return (NULL);
}

/*
//REVIEW - expand_env

//		Doubles the size of the environment.
		Save the new size in the env_size variable.
*/
int	expand_env(char ***env, int *env_size, t_exec *exec)
{
	char	**new_env;
	int		temp;

	if (cpy_env(*env, &new_env, env_size, &temp) == E_MALLOC)
		error(E_MALLOC, exec);
	*env_size *= 2;
	_free_matrix(*env);
	*env = new_env;
	return (0);
}

/*
//REVIEW - env_pars

//		The item to parse is divided in: 	PWD+=/execute
											PWD  	+=		/execute
											name	signs	content

//		Operations:
		1)	If the first element of the item is not a letter or a '_', 
			return error;
		2)	Skip characters until item[i] exists, 
			is a number, a letter or '_';
		3)	If the item[i] exists and is different than "=+",
			return error;
		4)	If you don't need to get other data, 
			return 0;
		5)	Set the size of the name to i;
		6)	Set the size of the signs to 1 if item[i] is a '=' or '+',
			otherwise set it to 0;
		7)	If item[i] is a '+' and item[i + 1] is a '=', increase signs
			to 1;
		8)	We go to the end of the item;
		9)	We set the size of cont_size to the difference of the total len
			of the item - no_eq_plus signs - name_size.
*/
int	env_pars(char *item, int *no_eq_plus, int *name_size, int *cont_size)
{
	int	i;

	if (!ft_isalpha(*item) && *item != '_')
		return (E_ENV_PARSING);
	i = 1;
	while (item[i] && (ft_isalnum(item[i]) || item[i] == '_'))
		++i;
	if (item[i] && item[i] != '=' && item[i] != '+')
		return (E_ENV_PARSING);
	else if (no_eq_plus == NULL)
		return (0);
	*name_size = i;
	*no_eq_plus = item[i] == '=' || item[i] == '+';
	if (item[i] == '+' && item[i + 1] == '=')
		*no_eq_plus += 1;
	while (item[i])
		++i;
	*cont_size = i - *no_eq_plus - *name_size;
	return (0);
}
