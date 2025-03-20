NAME = executor

SRC = 
SRC_DEBUG = debug.c 

OBJ_DIR = obj_executor

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_DEBUG = $(addprefix $(OBJ_DIR)/, $(SRC_DEBUG:.c=.o))

FLAGS = -Wall -Werror -Wextra -lreadline -lhistory -g

LIBFT = ../Ssj_libft/libft.a
DEBUG_LIBFT = debug_resources/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	cc -Wall -Werror -Wextra -g -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rcs $(NAME).a $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

deb: $(OBJ_DIR) $(OBJ) $(OBJ_DEBUG)
	mkdir -p $(OBJ_DIR)
	cc -D DEBUG=1 $(FLAGS) $(OBJ) $(OBJ_DEBUG) $(DEBUG_LIBFT) -o exe.out

clean:
	rm -rf obj_executor/*.o *.out
	rm -rf obj_executor

fclean: clean
	rm -rf $(NAME).a

re: fclean all

.PHONY: fclean re clean deb all