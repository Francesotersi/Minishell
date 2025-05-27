/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:43:54 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/27 10:41:53 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

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

/*
//REVIEW - realloc_env

//		Doubles the size of the environment.
		Save the new size in the env_size variable.
*/
int	realloc_env(char ***env, int *env_size, t_exec *exec)
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
	*no_eq_plus = (item[i] == '=' || item[i] == '+');
	if (item[i] == '+' && item[i + 1] == '=')
		*no_eq_plus += 1;
	while (item[i])
		++i;
	*cont_size = i - *no_eq_plus - *name_size;
	return (0);
}

int	increase_shell_level(char **env)
{
	int		i;
	int		shell_level;
	char	*shell_level_str;
	char	*temp;

	shell_level_str = get_env(env, "SHLVL");
	if (!shell_level_str)
		shell_level = 1;
	else
		shell_level = ft_atoi(shell_level_str) + 1;
	ft_getenv(env, "SHLVL", &i);
	temp = ft_itoa(shell_level);
	if (!temp)
		return (E_MALLOC);
	shell_level_str = ft_strjoin("SHLVL=", temp);
	free(temp);
	if (!shell_level_str)
		return (E_MALLOC);
	free(env[i]);
	env[i] = shell_level_str;
	return (0);
}

int	change_shell_name(char **env)
{
	int		i;
	char	*shell_name;
	char	*pwd;

	ft_getenv(env, "SHELL", &i);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (E_MALLOC);
	shell_name = ft_strjoin("SHELL=", pwd);
	free(pwd);
	if (!shell_name)
		return (E_MALLOC);
	free(env[i]);
	env[i] = shell_name;
	return (0);
}
