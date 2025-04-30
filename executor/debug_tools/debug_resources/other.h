/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:26:59 by alerusso          #+#    #+#             */
/*   Updated: 2025/03/06 15:58:43 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTHER_H
# define OTHER_H
# include "libft.h"
# include <stdarg.h>

int			add_sign_left(char **string, char sign);
int			add_sign_right(char **string, char sign);
int			cut_string(char *string, size_t start, size_t end);
int			cut_string_realloc(char **string, size_t start, size_t end);
void		*del_pointer(void **ptr, int mode);
void		*free_matrix(char **matrix);
void		*free_three_d_matrix(char ***matrix);
int			move_sign(char **type, char **name, char *sign);
int			ft_realloc(void **content, size_t nmemb, size_t size);
char		*ft_strjoin_free(char *s1, char *s2);
void		copy_stringset(char *dest, int charset_type);
void		copy_customset(char *dest, char *charset);
int			sub_strlen(char *s, char *charset, int mode);
int			sub_strcpy(char *dest, char *src, char *charset, int mode);
int			trim_only_right(char **line, char *trimset);
char		*ft_strjoin_var(char *which_del, int strings, ...);

#endif