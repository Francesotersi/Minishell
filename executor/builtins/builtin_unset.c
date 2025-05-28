/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:47:09 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/28 10:19:40 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static void	erase_one(char *item, char ***env, t_exec *exec);

/*
//REVIEW - ft_export

//		Unset can take any number of arguments.
		If there are no arguments, it does nothing, with ES 0.

//		Unset argument may be valid or invalid. There is a parsing for it.
		Valid arguments examples are:
		"MAN";	"_MAN2"; "__M_A_N".
		Invalid arguments examples are:
		"2MAN";	"*MAN"; "2MAN".
		To valid them, see env_pars function in environment.c.

//		If one argument is not valid, we do the following, but the ES will be
		set to 1.
		If there are pipes in the command line, the unset will not be done,
		but env_pars will still be done anyway.

//		Operations:
		1)	If there are no arguments, we do nothing;
		2)	For every argument in args, we loop using index i;
		3)	If the parsing succeds, and if there are no pipe, we remove the
			value in the environment (see below erase_one).
			Else if the parsing fails, we print an error message and set ES to
			1, and we go to the next argument.
*/
int	ft_unset(char **args, t_exec *exec)
{
	int		i;

	i = 1;
	set_exit_code(exec, 0);
	while (args[i])
	{
		if (!env_pars(args[i], NULL, NULL, NULL) && !ft_strchr(args[i], '='))
		{
			if (exec->at_least_one_pipe == _NO)
				erase_one(args[i], exec->env, exec);
		}
		else
		{
			bash_message(E_UNSET_PARSING, args[i]);
			set_exit_code(exec, 1);
		}
		++i;
	}
	return (0);
}

/*
//REVIEW - erase_one

//		Operations:
		1)	If the env does not exist, do nothing;
		2)	We loop for index i until we find the item.
			The item is the element to unset. make a strcmp
			until \0, +, =;
		3)	If you find the item, free it and set it to NULL;
		4)	Until you find the end of env matrix, move every env
			element following the item freed back to one place.
			example: (env1=one env2=two end3=three env4=four NULL)
			unset env2
					(env1=one NULL end3=three env4=four NULL)
					(env1=one end3=three env4=four NULL NULL)
		5)	We decrease the number of environment elements to
			one.
*/
static void	erase_one(char *item, char ***env, t_exec *exec)
{
	int	i;
	int	j;
	int	item_len;
	int	env_len;

	if (!*env || !(*env)[0])
		return ;
	i = -1;
	item_len = ft_strlen(item);
	while ((*env)[++i])
	{
		env_len = _sub_strlen((*env)[i], "+=", EXCL);
		if (!ft_strncmp(item, (*env)[i], item_len) && \
		!ft_strncmp(item, (*env)[i], env_len))
			break ;
	}
	if (!(*env)[i])
		return ;
	free((*env)[i]);
	(*env)[i] = NULL;
	j = i;
	while ((*env)[++j])
		(*env)[i++] = (*env)[j];
	(*env)[i] = NULL;
	*exec->last_env -= 1;
}
