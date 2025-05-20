NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c \
	ft_memcpy.c ft_memset.c ft_strchr.c ft_strdup.c ft_split.c\
	ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
	ft_toupper.c ft_putstr_fd.c ft_putchar_fd.c ft_putendl_fd.c\
	ft_putnbr_fd.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_memmove.c\
	ft_memcmp.c ft_hexprint_lower.c ft_hexprint_upper.c ft_printer.c\
	ft_printf.c ft_putaddress.c ft_retputnbr_fd.c ft_unsigned_putnbr_fd.c\
	ft_utils.c get_next_line_bonus.c get_next_line_utils_bonus.c

OBJ = $(SRC:.c=.o)

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
	ft_lstmap.c

OBJ_BONUS = $(BONUS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

all: $(NAME)
	@echo Making yo mama happy...

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

clean:
	@echo Cleaning less Shit be patient....
	@$(RM) *.o

fclean: clean
	@echo BE FUCKING PATIENT!!!!!!
	@$(RM) $(NAME)

re: fclean all

bonus: $(OBJ) $(OBJ_BONUS)
	@ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)

.PHONY: all fclean clean re bonus