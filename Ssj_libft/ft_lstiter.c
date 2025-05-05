/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:49:21 by ftersill          #+#    #+#             */
/*   Updated: 2024/12/03 16:32:26 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// static void print_content(void *content)
// {
//     printf("%d\n", *(int *)content);
// }

// int main()
// {
//     int val1 = 42;
//     int val2 = 24;
//     int val3 = 53;

//     t_list *lst1 = ft_lstnew(&val1);
//     t_list *lst2 = ft_lstnew(&val2);
//     t_list *lst3 = ft_lstnew(&val3);
//     lst1->next = lst2;
//     lst2->next = lst3;
//     printf("Lista di valori:\n");
//     ft_lstiter(lst1, print_content);
//     free(lst1);
//     free(lst2);
//     free(lst3);
//     return 0;
// }
