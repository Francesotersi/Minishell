/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mfile_gnl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:13:36 by alerusso          #+#    #+#             */
/*   Updated: 2025/02/21 11:25:23 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Memoria statica usata ---> BUFFER_SIZE * 4000
// Define per il debug
#ifndef MFILE_GNL_H
# define MFILE_GNL_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# define COUNTER 100000000
# define FORCE_READ_ONE_TEXT 0
// Define usati nel programma
# define FIND 1
# define GET 2
# define MOVE 3
# define SHORTWORDS_LEN 4
# define MIDWORDS_LEN 10
# define RESET -2
# define MALLOC 1
# define REALLOC 2
# define FREE 3
# define CALLOC 4
# define MEMCPY 5
# define FULL_MEMORY -1
# define SUCCESS 1
# define NO_NEWLINE_FOUND 0
# define EOF_OR_NEWLINE_FOUND 1
# define EOF_OR_NEWLINE_NOT_FOUND -1
# define EMPTY_BUFFER 0
# define END_OR_CORRUPTION -1
// Librerie
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <malloc.h>
# include <fcntl.h>
# include <limits.h>
# include "structs.h"
# include "other.h"

typedef unsigned char	t_ob;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

//		ORIGINAL GNL
char	*gnl(int fd);
char	*gnl_original_main_function(int fd, char buffer[BUFFER_SIZE + 1]);
char	*get(char **store_bytes, char buffer[BUFFER_SIZE + 1], int nl, int fd);
int		go_read(int fd, char buffer[BUFFER_SIZE + 1], char **new_line);
int		loop_read(char **new_line, int *control_read, size_t *end, int fd);
int		alloc_ft(void **content, void *new_content, size_t start, int mode);
int		find_end_line(size_t *start, char *string);
void	*calloc_memcpy(int size, void *dest, const void *src, int ft);
void	trim_readbytes(char *buffer);
char	*ft_strjoin_custom(char *s1, char *s2);
//		WRITE_LINE SETTINGS

int		set_maximum_word_len(int new_len);
int		set_maximum_words(int new_len);
//		INITIATE FILE

void	initiate_file_demo(int fd, char *name);
void	initiate_file(int fd, char *name, char **matrix);
//		CUSTOM GNL (DONT USE IT!!)

char	*get_next_line(int fd, int reset);
char	*read_from_buffer(char buffer[BUFFER_SIZE + 1], int fd, int bytes);
char	*get_next_line_main_function(int fd, char buffer[BUFFER_SIZE + 1]);
//		DONT USE THESE: ONLY FOR LIBRARY PURPOSES!

int		find_line(int fd, int num_search, va_list list);
int		find_number_line(int fd, char *filename, int num_search, ...);
//		EXPANDED MANAGE_FILE FUNCTIONS

int		num_line(int num_search, ...);
void	hold_space(int counter, int fd);
int		move_cursor(int line_num);
char	*read_line(int line_num, int position);
char	**read_all_line(int line_num);
int		write_line(int line_num, int position, char *string);
char	*get_n_line(int fd, int n);
int		reset_fd(int fd, char *name);
int		get_filedata(int *fd, char **filename);
int		give_filedata(int fd, char *filename);
int		del_filedata(void);
int		switch_filedata(int fd);
int		update_filedata(int old_fd, int new_fd);

#endif