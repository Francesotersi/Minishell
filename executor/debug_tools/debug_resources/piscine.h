/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piscine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:34:19 by alerusso          #+#    #+#             */
/*   Updated: 2025/02/20 12:44:03 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PISCINE_H
# define PISCINE_H

char	*ft_strcapitalize(char *str);
char	*ft_convert_base(char *nbr, char *base_from, char *base_to);
int		ft_iterative_factorial(int nb);
int		ft_find_next_prime(int nb);
int		ft_str_is_lowercase(char *str);
int		ft_str_is_uppercase(char *str);
int		ft_is_prime(int nb);
int		ft_iterative_power(int nb, int power);
void	ft_rev_int_tab(int *tab, int size);
void	ft_sort_int_tab(int *tab, int size);
int		ft_sqrt(int nb);
char	*ft_strlowcase(char *str);

#endif