/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:44:37 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/28 10:17:32 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static void	is_flag(char *s, char *print_slash_n, int *j, char *stop_check);
static int	is_n(char *s, int *j);

/*
//REVIEW - ft_echo

//		Echo gets the flag -n, therefore it needs a particular parsing.

//		Normally, echo prints a \n at the end. The flag -n silents it.

//		Echo must not print anything, while it finds flags.
		Therefore, for:
		"-n -n -n -n -n -na Hello world!"
		Must print:
		"-na Hello world!"	/without \n.
		We've registered this info with two variables:
			print_slash_n: 	bool that checks if \n must be printed (starts 1);
			stop_check:		bool that stops checking for flags (starts 0).

//		When all args are printed, we call write to prints \n:
		write(1, "\n", (int)print_slash_n);
		Therefore, if print_slash_n is set to 0, it does not print anything.

//		Operations:
		1)	For every argument in args, we loop using index i;
		2)	For every character of the arg, we loop using index j;
		3)	If stop_check has not been already set to YES,
			we enter in is_flag (see below). We pass the address of the char.
			Otherwise, we simply prints the character.
		4) 	We call write to print the final \n, using print_slash_n.

*/
int	ft_echo(char **args, t_exec *exec)
{
	int		i;
	int		j;
	char	print_slash_n;
	char	stop_check;

	(void)exec;
	i = 1;
	print_slash_n = _YES;
	stop_check = _NO;
	set_exit_code(exec, 0);
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (stop_check == _NO)
				is_flag(&args[i][j], &print_slash_n, &j, &stop_check);
			else
				write(1, &args[i][j], 1);
			++j;
		}
		if (args[++i] && stop_check == _YES)
			write(1, " ", 1);
	}
	return (write(1, "\n", (int)print_slash_n));
}

/*
//REVIEW - is_flag

//		Valid flags are:
		"-n";	"-n ";	" -n";	" -n ";	"-n -n".
		Invalid flags are:
		"X-n";	"-nX";	"X-nX";	" -m ";	"-n-n".
		To valid them, we need to:
		1)	Check if the previous char NOT exists (j == 0) or is a SPACE.
			In every other cases, the flag is not valid.
		2)	Check if the first char is a '-', the second a 'n', the last
			a SPACE or a \0 character.

//		If true, we skip 3 characters (ft_echo always increase j) and set
		print_slash_n to NO. To avoid out of bond access, we decrease j
		to one if, skipping two characters, we reach \0.

/		If false, we write the current character, and set stop_check to YES.
*/
static void	is_flag(char *s, char *print_slash_n, int *j, char *stop_check)
{
	if (s[0] == '-' && is_n(s, j))
	{
		*print_slash_n = _NO;
	}
	else
	{
		write(1, s, 1);
		*stop_check = _YES;
	}
}

static int	is_n(char *s, int *j)
{
	int	i;

	i = 1;
	while (s[i] == 'n')
		++i;
	if (s[i])
		return (_NO);
	*j = i - 1;
	return (_YES);
}

/*
int	main()
{
	char	*args1[] = {"/bin/echo", "Assurdo", "Impossibile", "Tremendo", \
	NULL};
	char	*args2[] = {"/bin/echo", "-n", " Impossibile", " Tremendo", NULL};
	char	*args3[] = {"/bin/echo", " -n", "Impossibile", " -n", NULL};
	char	*args4[] = {"/bin/echo", "-n-", "n-", "-n", "n- n- n- n", \
		"Impossibile", \
	"Tremendo", NULL};
	char	*args5[] = {"/bin/echo", "-nnnnn", "-na", "Impossibile", \
	"Tremendo", NULL};
	char	*args6[] = {"/bin/echo", "    -n -n -n -n -n -na", "Impossibile",\
	 "Tremendo", NULL};
	char	*args7[] = {"/bin/echo", NULL};
	char	*args8[] = {"/bin/echo", "|", "",\
		"   |", NULL};
	char	*args9[] = {"/bin/echo", "-nnnnn -n -nnn -nmn -n  ", "yis",\
		"   |", NULL};
	
	write(1, "TEst 1: |Assurdo Impossibile Tremendo\n|\n\t|", 43);
	ft_echo(args1, NULL);
	write(1, "|\n", 2);
	write(1, "TEst 2: |  Impossibile  Tremendo|\n\t|", 36);
	ft_echo(args2, NULL);
	write(1, "|\n", 2);
	write(1, "TEst 3: | -n Impossibile  -n\n|\n\t|", 34);
	ft_echo(args3, NULL);
	write(1, "|\n", 2);
	write(1, "TEst 4: |-n- n- -n n- n- n- n Impossibile Tremendo\n|\n\t|", 55);
	ft_echo(args4, NULL);
	write(1, "|\n", 2);
	write(1, "TEst 5: | -na Impossibile Tremendo|\n\t|", 38);
	ft_echo(args5, NULL);
	write(1, "|\n", 2);
	write(1, "TEst 6: |    -n -n -n -n -n -na Impossibile Tremendo\n|\n\t|", 57);
	ft_echo(args6, NULL);
	write(1, "|\n", 2);
	write(1, "TEst 7: |\n|\n\t|", 14);
	ft_echo(args7, NULL);
	write(1, "|\n", 2);
	write(1, "TEst 8: ||     |\n|\n\t|", 21);
	ft_echo(args8, NULL);
	write(1, "|\n", 2);
	write(1, "TEst 9: |-nnnnn -n -nnn -nmn -n   yis    |\n|\n\t|", 47);
	ft_echo(args9, NULL);
	write(1, "|\n", 2);
}
*/
