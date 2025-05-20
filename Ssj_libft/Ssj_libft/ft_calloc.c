/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:48:25 by ftersill          #+#    #+#             */
/*   Updated: 2024/12/11 15:10:58 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*bezero;
	size_t			b;
	size_t			n;
	void			*a;

	b = 0;
	n = (nmemb * size);
	a = malloc(n);
	if (a == NULL)
		return (NULL);
	bezero = (unsigned char *)a;
	while (b < n)
	{
		bezero[b] = 0;
		b++;
	}
	return (a);
}

/* nt main()
{
    // Caso 1:  0, size = 0
    void *ptr1 = ft_calloc(0, 0);
    if (ptr1 == NULL)
        printf("Test 1 passed: NULL pointer returned for nmemb=0, size=0\n");
    else
        printf("Test 1 failed: Non-NULL pointer returned for nmemb=0, size=0\n");

    // Caso 2: nmemb > 0, size = 0 (allocazione per zero byte)
    void *ptr2 = ft_calloc(10, 0);
    if (ptr2 == NULL)
        printf("Test 2 failed: NULL pointer returned for nmemb=10, size=0\n");
    else
        printf("Test 2 passed: Memory allocated with nmemb=10, size=0\n");

    // Caso 3: nmemb = 0, size > 0
    void *ptr3 = ft_calloc(0, 10);
    if (ptr3 == NULL)
        printf("Test 3 passed: NULL pointer returned for nmemb=0, size=10\n");
    else
        printf("Test 3 failed: Non-NULL pointer for nmemb=0, size=10\n");

    // Caso 4: nmemb = 1, size = 10 (allocazione di memoria per 10 byte)
    void *ptr4 = ft_calloc(1, 10);
    if (ptr4 != NULL)
        printf("Test 4 passed: Memory allocated for 10 bytes\n");
    else
        printf("Test 4 failed: Memory allocation failed for 10 bytes\n");

    // Caso 5: nmemb molto grande, size piccolo (overflow potenziale)
    void *ptr5 = ft_calloc(SIZE_MAX, 1);
    if (ptr5 == NULL)
        printf("Test 5 passed: Memory allocation failed for large nmemb\n");
    else
        printf("Test 5 failed: Memory allocated despite large nmemb\n");

    // Caso 6: nmemb piccolo, size molto grande (overflow potenziale)
    void *ptr6 = ft_calloc(1, SIZE_MAX);
    if (ptr6 == NULL)
        printf("Test 6 passed: Memory allocation failed for large size\n");
    else
        printf("Test 6 failed: Memory allocated despite large size\n");

    // Caso 7: nmemb e size grandi che causano un overf nella molti
    void *ptr7 = ft_calloc(SIZE_MAX / 2, 2);
    if (ptr7 == NULL)
        printf("Test 7 passed: Memory allocation failed due to overflow\n");
    else
        printf("Test 7 failed: Memory allocated despite overflow\n");

    // Caso 8: allocazione regolare (allocdi 10 blocchi da 10 b ciascuno)
    void *ptr8 = ft_calloc(10, 10);
    if (ptr8 != NULL)
        printf("Test 8 passed: Memory allocated for 100 bytes\n");
    else
        printf("Test 8 failed: Memory allocation failed for 100 bytes\n");

    // Pulizia della memoria
    free(ptr4);
    free(ptr8);
    free(ptr5);
    free(ptr6);
    free(ptr7);

    return 0;
} */

// int main()
// {
//     int n = 2;
//     char *str = (char*)ft_calloc(n, sizeof(char));
//     if (str == NULL)
//         return 1;
//     str[0] = 'A';
//     str[1] = '\0'; 
//     printf("%s\n", str);

//     return 0;
// }