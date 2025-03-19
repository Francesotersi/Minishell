NAME = parsing

SRC = debug.c
SRC_DEBUG = debug.c 

OBJ_DIR = obj_parsing

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_DEBUG = $(addprefix $(OBJ_DIR)/, $(SRC_DEBUG:.c=.o))

FLAGS = -Wall -Werror -Wextra -lreadline -lhistory -g

LIBFT = ../Ssj_libft/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rcs $(NAME).a $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

%.o: %.
	$(CC) $(CFLAGS) -c $< -o $@

debug: $(OBJ_DIR)$(OBJ) $(OBJ_DEBUG)
	mkdir -p $(OBJ_DIR)
	cc $(FLAGS) $(LIBFT) $(OBJ) $(OBJ_DEBUG) -o $(NAME)

clean:
	rm -rf obj_parsing/*.o
	rm -rf obj_parsing

fclean: clean
	rm -rf $(NAME).a

re: fclean all

.PHONY: fclean re clean debug all