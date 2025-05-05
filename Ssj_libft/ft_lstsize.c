/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:05:46 by ftersill          #+#    #+#             */
/*   Updated: 2024/12/03 16:32:12 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int			i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

// int main()
// {
// 	t_list	**pinco = (t_list**)malloc(sizeof(t_list *) * 3);
// 	t_list	*p = ft_lstnew("sbusto");
// 	t_list	*p2 = ft_lstnew("perforzingher");
// 	t_list	*p3 = ft_lstnew("Mario Sturniolo");
// 	ft_lstadd_front(pinco, p3);
// 	ft_lstadd_front(pinco, p2);
// 	ft_lstadd_front(pinco, p);
// 	printf("%d", ft_lstsize(*pinco));
// 	return (0);
// }