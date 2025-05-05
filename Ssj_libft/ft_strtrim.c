/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 08:52:04 by ftersill          #+#    #+#             */
/*   Updated: 2024/12/03 17:04:18 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//caratteri da saltare dall`inizio
static int	ft_start(char const *rts, char const *tes)
{
	int	l;
	int	m;
	int	value;

	l = 0;
	m = 0;
	value = 0;
	while (rts[l] != '\0')
	{
		while (tes[m] != '\0')
		{
			if (rts[l] == tes[m])
			{
				value++;
				m = 0;
				break ;
			}
			m++;
		}
		l++;
	}
	return (value);
}
//caratteri da saltare dalla fine

static int	ft_finish(const char *rts, const char *tes)
{
	int	l;
	int	m;
	int	value;

	l = ft_strlen(rts) - 1;
	m = 0;
	value = 0;
	while (l >= 0)
	{
		while (tes[m] != '\0')
		{
			if (rts[l] == tes[m])
			{
				value++;
				m = 0;
				break ;
			}
			m++;
		}
		l--;
	}
	return (value);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*a;
	size_t	front;
	size_t	back;
	size_t	b;

	if (!s1)
		return (NULL);
	front = ft_start(s1, set);
	back = ft_strlen(s1) - ft_finish(s1, set);
	a = (char *)malloc(sizeof(char) * (back + 1));
	if (!a)
		return (NULL);
	b = 0;
	while (front < back)
	{
		a[b] = s1[front];
		b++;
		front++;
	}
	a[b] = '\0';
	return (a);
}

// int main()
// {
// 	char *gif = "\t   \n\n\n  \n\n\t    Hello \t  Please\n Trim me !";
// 	char *neg = "Hello \t  Please\n Trim me !";
// 	char *s = ft_strtrim(gif, neg);
// 	printf("|%s|\n", s);
// 	free(s);
// }

// #include "libft.h"
// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     // Test 1: Stringa vuota
//     char *test1 = "";
//     char *set1 = "";
//     char *result1 = ft_strtrim(test1, set1);
//     printf("Test 1 (empty string): '%s'\n", result1);
//     free(result1);

//     // Test 2: Stringa senza caratteri da rimuovere
//     char *test2 = "hello";
//     char *set2 = "xyz";
//     char *result2 = ft_strtrim(test2, set2);
//     printf("Test 2 (no characters to remove): '%s'\n", result2);
//     free(result2);

//     // Test 3: Stringa con solo caratteri da rimuovere
//     char *test3 = "   hello   ";
//     char *set3 = " ";
//     char *result3 = ft_strtrim(test3, set3);
//     printf("Test 3 (only spaces to trim): '%s'\n", result3);
//     free(result3);

//     // Test 4: Caratteri da rimuovere all'inizio e alla fine
//     char *test4 = "!!hello!!";
//     char *set4 = "!";
//     char *result4 = ft_strtrim(test4, set4);
//     printf("Test 4 (characters to trim at both ends): '%s'\n", result4);
//     free(result4);

//     // Test 5: Caratteri da rimuovere solo all'inizio
//     char *test5 = "   hello";
//     char *set5 = " ";
//     char *result5 = ft_strtrim(test5, set5);
//     printf("Test 5 (spaces only at the start): '%s'\n", result5);
//     free(result5);

//     // Test 6: Caratteri da rimuovere solo alla fine
//     char *test6 = "hello   ";
//     char *set6 = " ";
//     char *result6 = ft_strtrim(test6, set6);
//     printf("Test 6 (spaces only at the end): '%s'\n", result6);
//     free(result6);

//     // Test 7: Stringa con caratteri speciali
//     char *test7 = "@hello@";
//     char *set7 = "@";
//     char *result7 = ft_strtrim(test7, set7);
//     printf("Test 7 (special characters): '%s'\n", result7);
//     free(result7);

//     // Test 8: Set vuoto (non deve rimuovere nulla)
//     char *test8 = "hello";
//     char *set8 = "";
//     char *result8 = ft_strtrim(test8, set8);
//     printf("Test 8 (empty set): '%s'\n", result8);
//     free(result8);

//     // Test 9: Stringa con solo set di caratteri
//     char *test9 = "###";
//     char *set9 = "#";
//     char *result9 = ft_strtrim(test9, set9);
//     printf("Test 9 (only set characters): '%s'\n", result9);
//     free(result9);

//     // Test 10: Set contiene la stringa completa
//     char *test10 = "hello";
//     char *set10 = "hello";
//     char *result10 = ft_strtrim(test10, set10);
//     printf("Test 10 (set contains the whole string): '%s'\n", result10);
//     free(result10);

//     return 0;
// }