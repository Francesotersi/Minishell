/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftersill <ftersill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:34:10 by ftersill          #+#    #+#             */
/*   Updated: 2025/01/15 10:52:26 by ftersill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>

//libft
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
int		ft_isalnum(int i);
int		ft_isalpha(int c);
int		ft_isascii(int i);
int		ft_isdigit(int i);
int		ft_isprint(int i);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
int		ft_lstsize(t_list *lst);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char	*dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *source, size_t size);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
//ft_printf
int		ft_hexprint_lower(unsigned int nb);
int		ft_hexprint_upper(unsigned int nb);
int		ft_printer(const char *str, va_list(arglist));
int		ft_printf(const char *str, ...);
int		ft_putaddress(unsigned long long nb);
int		ft_retputnbr_fd(int n, int fd);
int		ft_unsigned_putnbr_fd(unsigned int n, int fd);
int		ft_unsigned_numlen(unsigned int nb);
int		ft_numlen(int nb);
int		ft_putstr_count_fd(char *s, int fd);
int		ft_putchar_count_fd(char c, int fd);
int		ft_putaddress_check(unsigned long long nb);
int		ft_intcheck(int n, int fd);
//gte_next_line e` la versione bonus quella importata
char	*get_next_line_bonus(int fd);
char	*ft_roll_and_print(char *line);
char	*ft_check_read(int fd, char *statik, char *buffer);
char	*ft_strchr_new(char *s);
char	*ft_strjoin_get(char *s1, char *s2);
char	*ft_substr_get(char *s, unsigned int start, size_t len);
size_t	ft_strlen_get(char *s);
char	*ft_strdup_get(char *s1);

#endif