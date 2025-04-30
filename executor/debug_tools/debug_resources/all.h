/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:36:04 by alerusso          #+#    #+#             */
/*   Updated: 2025/03/06 15:59:03 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H
# include "libft.h"
# include "other.h"
# include "mfile_gnl.h"
# include "piscine.h"
# include "game_bfs.h"

//	BIG LIST
//	--LIBFT:

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

//	--PISCINE:

char		*ft_strcapitalize(char *str);
char		*ft_convert_base(char *nbr, char *base_from, char *base_to);
int			ft_iterative_factorial(int nb);
int			ft_find_next_prime(int nb);
int			ft_str_is_lowercase(char *str);
int			ft_str_is_uppercase(char *str);
int			ft_is_prime(int nb);
int			ft_iterative_power(int nb, int power);
void		ft_rev_int_tab(int *tab, int size);
void		ft_sort_int_tab(int *tab, int size);
int			ft_sqrt(int nb);
char		*ft_strlowcase(char *str);
//	--OTHER:

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

//	--MFILE

//		ORIGINAL GNL
char		*gnl(int fd);
char		*gnl_original_main_function(int fd, char buffer[BUFFER_SIZE + 1]);
char		*get(char **store_bytes, char buffer[BUFFER_SIZE + 1], \
	int nl, int fd);
int			go_read(int fd, char buffer[BUFFER_SIZE + 1], char **new_line);
int			loop_read(char **new_line, int *control_read, size_t *end, int fd);
int			alloc_ft(void **content, void *new_content, size_t start, int mode);
int			find_end_line(size_t *start, char *string);
void		*calloc_memcpy(int size, void *dest, const void *src, int ft);
void		trim_readbytes(char *buffer);
char		*ft_strjoin_custom(char *s1, char *s2);
//		WRITE_LINE SETTINGS

int			set_maximum_word_len(int new_len);
int			set_maximum_words(int new_len);
//		INITIATE FILE

void		initiate_file_demo(int fd, char *name);
void		initiate_file(int fd, char *name, char **matrix);
//		CUSTOM GNL (DONT USE IT!!)

char		*get_next_line(int fd, int reset);
char		*read_from_buffer(char buffer[BUFFER_SIZE + 1], int fd, int bytes);
char		*get_next_line_main_function(int fd, char buffer[BUFFER_SIZE + 1]);
//		DONT USE THESE: ONLY FOR LIBRARY PURPOSES!

int			find_line(int fd, int num_search, va_list list);
int			find_number_line(int fd, char *filename, int num_search, ...);
//		EXPANDED MANAGE_FILE FUNCTIONS

int			num_line(int num_search, ...);
void		hold_space(int counter, int fd);
int			move_cursor(int line_num);
char		*read_line(int line_num, int position);
char		**read_all_line(int line_num);
int			write_line(int line_num, int position, char *string);
char		*get_n_line(int fd, int n);
int			reset_fd(int fd, char *name);
int			get_filedata(int *fd, char **filename);
int			give_filedata(int fd, char *filename);
int			del_filedata(void);
int			switch_filedata(int fd);
int			update_filedata(int old_fd, int new_fd);
//	--GAME:

t_typelist	*store_list(t_typelist *list, int mode);
void		del_free(void *ptr);
int			draw_path(t_bfs *bfs);
void		bfs(t_bfs *bfs);
void		clean_bfs(t_bfs *bfs, int enemy_num);
//int	    get_best_path(t_map *map, int enemy_num);

#endif