/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:30:58 by alerusso          #+#    #+#             */
/*   Updated: 2025/02/24 09:45:23 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <unistd.h>
# include <malloc.h>
# include <limits.h>
# include <fcntl.h>
# include "structs.h"

typedef struct s_typelist
{
	void	*content;
	void	*type;
	void	*next;
}				t_typelist;

enum e_charsets
{
	ALPHA,
	UPPER_ALPHA,
	LOWER_ALPHA,
	DIGIT,
	ALPHANUM,
	EXCLUDE,
	INCLUDE,
};

enum e_bool
{
	ON = 1,
	YES = 1,
	OFF = 0,
	NO = 0,
};

int			ft_atoi(const char *nptr);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
char		*ft_itoa(int num);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(const char *str);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
//		LIST

t_typelist	*ft_lstnew(void *content, void *type);
void		ft_lstadd_front(t_typelist **lst, t_typelist *new);
int			ft_lstsize(t_typelist *lst);
t_typelist	*ft_lstlast(t_typelist *lst);
void		ft_lstadd_back(t_typelist **lst, t_typelist *new);
void		ft_lstdelone(t_typelist *lst, void (*del)(void *));
void		ft_lstclear(t_typelist **lst, void (*del)(void *));
void		ft_lstiter(t_typelist *lst, void (*f)(void *));
t_typelist	*ft_lstmap(t_typelist *lst, void *(*f)(void *), \
void (*del)(void *));
//		PRINTF

int			l_printf(const char *str, ...);
int			fd_printf(int fd, const char *str, ...);

#endif
