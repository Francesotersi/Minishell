/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:08:50 by ftersill          #+#    #+#             */
/*   Updated: 2024/12/03 17:21:54 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new;

	if (!lst)
		return (NULL);
	new = NULL;
	while (lst)
	{
		f(lst->content);
		new_list = ft_lstnew(lst->content);
		if (!lst)
		{
			del(lst->content);
			free(lst);
		}
		ft_lstadd_back(&new, new_list);
		lst = lst->next;
	}
	return (new);
}

// void *transform_content(void *content) {
//     int *new_content = (int *)malloc(sizeof(int));
//     if (!new_content)
//         return (NULL);
//     *new_content = (*(int *)content) * 2; 
//     return (new_content);
// }

// void del(void *content) 
// {
//     if (content)
//         printf("Content deleted: %s\n", (char *)content);
// }

// void print_list(t_list *lst) {
//     while (lst) {
//         printf("%d -> ", *(int *)lst->content);
//         lst = lst->next;
//     }
//     printf("NULL\n");
// }

// int main() {
//     // Creazione della lista
//     t_list *list = NULL;
//     int *num1 = malloc(sizeof(int));
//     int *num2 = malloc(sizeof(int));
//     int *num3 = malloc(sizeof(int));
//     *num1 = 1;
//     *num2 = 2;
//     *num3 = 3;

//     ft_lstadd_back(&list, ft_lstnew(num1));
//     ft_lstadd_back(&list, ft_lstnew(num2));
//     ft_lstadd_back(&list, ft_lstnew(num3));

//     // Stampa la lista originale
//     printf("Lista originale:\n");
//     print_list(list);

//     // Applica ft_lstmap alla lista
//     t_list *mapped_list = ft_lstmap(list, transform_content, del);

//     // Stampa la lista trasformata
//     printf("Lista trasformata:\n");
//     print_list(mapped_list);

//     // Liberazione della memoria
//     while (list) {
//         t_list *temp = list;
//         list = list->next;
//         del(temp->content);
//         free(temp);
//     }

//     while (mapped_list) {
//         t_list *temp = mapped_list;
//         mapped_list = mapped_list->next;
//         del(temp->content);
//         free(temp);
//     }

//     return 0;
// }
