/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:52:22 by ftersill          #+#    #+#             */
/*   Updated: 2025/01/28 15:11:54 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_string_copy(char *dest, const char *source, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return ;
	while (source[i] != '\0' && i < size - 1)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
}

static char	**ft_free(char **matrix)
{
	char	**temp;

	temp = matrix;
	while (*temp != NULL)
	{
		free(*temp);
		temp++;
	}
	free(matrix);
	return (NULL);
}

static char	**ft_copy(const char *s, char c, char **matrix)
{
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\0')
	{
		len = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			len++;
			i++;
		}
		if (len > 0)
		{
			matrix[j] = (char *)malloc(sizeof(char) * (len + 1));
			if (!matrix[j])
				return (ft_free(matrix));
			ft_string_copy(matrix[j++], s + (i - len), len + 1);
		}
	}
	return (matrix);
}

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		count++;
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		words_number;

	words_number = ft_count_words(s, c);
	matrix = (char **)malloc(sizeof(char *) * (words_number + 1));
	if (!matrix)
		return (NULL);
	matrix = ft_copy(s, c, matrix);
	if (matrix)
		matrix[words_number] = NULL;
	return (matrix);
}

// void print_split_result(char **result)
// {
//     if (!result)
//     {
//         printf("Null pointer\n");
//         return;
//     }

//     int i = 0;
//     while (result[i])
//     {
//         printf("Word %d: '%s'\n", i, result[i]);
//         i++;
//     }
// }

// int main()
// {
//     // Test case 1: Stringa normale con spazio come delimitatore
//     char *s1 = "Hello World Test String";
//     char **result1 = ft_split(s1, ' ');
//     printf("Test case 1 (normal string with spaces):\n");
//     print_split_result(result1);
//     free(result1);

//     // Test case 2: Stringa con più delimitatori consecutivi
//     char *s2 = "Hello  World  Test";
//     char **result2 = ft_split(s2, ' ');
//     printf("\nTest case 2 (multiple spaces between words):\n");
//     print_split_result(result2);
//     free(result2);

//     // Test case 3: Stringa senza delimitatori
//     char *s3 = "HelloWorld";
//     char **result3 = ft_split(s3, ' ');
//     printf("\nTest case 3 (no spaces):\n");
//     print_split_result(result3);
//     free(result3);

//     // Test case 4: Stringa vuota
//     char *s4 = "";
//     char **result4 = ft_split(s4, ' ');
//     printf("\nTest case 4 (empty string):\n");
//     print_split_result(result4);
//     free(result4);

//     // Test case 5: Stringa con solo delimitatori
//     char *s5 = "   ";
//     char **result5 = ft_split(s5, ' ');
//     printf("\nTest case 5 (string with only spaces):\n");
//     print_split_result(result5);
//     free(result5);

//     // Test case 6: Stringa con delimitatori all'inizio e alla fine
//     char *s6 = "   Hello   World   ";
//     char **result6 = ft_split(s6, ' ');
//     printf("\nTest case 6 (spaces at the beginning and end):\n");
//     print_split_result(result6);
//     free(result6);

//     // Test case 7: Delimitatore non presente nella stringa
//     char *s7 = "Hello,World,Test";
//     char **result7 = ft_split(s7, ',');
//     printf("\nTest case 7 (using ',' as delimiter):\n");
//     print_split_result(result7);
// 	free(result7);

//     //Test case 8: Delimitatore uguale a 0 (no split)
//     char *s8 = "\0cazzo\0\0\0\0\0cioa\0\0\0\0";
//     char **result8 = ft_split(s8, 0);
//     printf("\nTest case 8 (delimiter = 0):\n");
//     print_split_result(result8); // Should print null pointer or sim.
//     free(result8);

//     return 0;
// }
