NAME = parsing

SRC = start_lexing.c fill_struct.c utils.c struct_alloc.c remove_quotes.c \
	define_token.c define_token_2.c expand_env.c expand_env_2.c utils_2.c \
	parenthesis.c expand_wildcard.c parser.c ../set_signals.c\

SRC_DEBUG = debug.c 

OBJ_DIR = obj_parsing

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_DEBUG = $(addprefix $(OBJ_DIR)/, $(SRC_DEBUG:.c=.o))

FLAGS = -Wall -Werror -Wextra -lreadline -lhistory -g

CFLAGS = -Wall -Werror -Wextra -g

LIBFT = ../Ssj_libft/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
# ar rcs $(NAME).a $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: $(OBJ_DIR)$(OBJ) $(OBJ_DEBUG)
	mkdir -p $(OBJ_DIR)
	cc $(FLAGS) $(LIBFT) $(OBJ) $(OBJ_DEBUG) -o $(NAME)

clean:
	rm -rf obj_parsing/*.o
	rm -rf obj_parsing

fclean: clean

re: fclean all

.PHONY: fclean re clean debug all