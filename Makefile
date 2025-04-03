NAME = minishell

SRC = main.c signals.c

OBJ_DIR = obj_main

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

FLAGS = -g -Wall -Werror -Wextra -lreadline -lhistory -lncurses -ISsj_libft

LIBFT = Ssj_libft/libft.a

PARSING = parsing/parsing.a

EXECUTOR = executor/executor.a

all : $(NAME)

$(OBJ_DIR)/%.o: %.c
	cc -g -Wall -Werror -Wextra -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	make bonus -C Ssj_libft
	make -C parsing
	make -C executor
	cc $(OBJ) $(EXECUTOR) $(PARSING) $(LIBFT) $(FLAGS) -o $(NAME)
	

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

parsing:
	make bonus -C Ssj_libft
	make -C parsing
	cc $(FLAGS) $(LIBFT) $(OBJ) -o $(NAME)

executor:
	make bonus -C Ssj_libft
	make -C executor
	cc $(FLAGS) $(LIBFT) $(OBJ) -o $(NAME)

clean:
	@echo Cleaning...
	make clean -C Ssj_libft
	make clean -C parsing
	make clean -C executor
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo I SAID I AM CLEANING OK!!
	make fclean -C Ssj_libft
	make fclean -C parsing
	make fclean -C executor
	rm -f minishell

re : fclean all

libft:
	@echo Compiling Ssj_Libft...
	make bonus -C Ssj_libft

.PHONY: parsing executor clean fclean re

# .SILENT:
