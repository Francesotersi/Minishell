NAME = executor

COMMON_CORE = ../../
OBJ_DIR = 		obj_executor
BONUS_DIR = 	bonus
BUILT_DIR = 	builtins
DEBUG_DIR =		debug_tools
ENV_DIR =		env_management
EXEC_DIR = 		execution_main
MEM_DIR = 		memory_management
PREP_DIR = 		execution_prep
UTILS_DIR = 	utils

#NOTE - To understand execution part, reading  
#		execute.c from execution_main/ should be enough.

#SECTION - Bonus files
BONUS_FILES = 			bonus_parenthesis.c bonus_wildcards1.c bonus_wildcards2.c
BONUS = 				$(addprefix $(BONUS_DIR)/, $(BONUS_FILES))

#SECTION - Builtin files
BUILTINS_FILES = 		builtin_cd.c builtin_echo.c builtin_env.c \
						builtin_exit.c builtin_export.c builtin_pwd.c \
						builtin_unset.c
BUILTINS = 				$(addprefix $(BUILT_DIR)/, $(BUILTINS_FILES))

#SECTION - env2 fts are meant to be used in parsing part
ENV_FILES = 			environment.c environment2.c
ENV = 					$(addprefix $(ENV_DIR)/, $(ENV_FILES))

#SECTION - execution main file, and errors printings
EXECUTION_MAIN_FILES = 	error_message.c execute.c
EXECUTION_MAIN = 		$(addprefix $(EXEC_DIR)/, $(EXECUTION_MAIN_FILES))

#SECTION - Modify tokens, open here docs, prepare commands, get commands paths
EXECUTION_PREP_FILES = 	get_commands_data.c get_file_data.c \
						get_paths_data.c get_tokens.c
EXECUTION_PREP =		$(addprefix $(PREP_DIR)/, $(EXECUTION_PREP_FILES))

#SECTION - allocate, get memory from main program, free
MEMORY_FILES = 			memory.c
MEMORY = 				$(addprefix $(MEM_DIR)/, $(MEMORY_FILES))

#SECTION - General utilities to abstract part of program
UTILS_FILES = 			printf_fd.c utils_count.c utils_debug.c utils_fds.c \
						utils_generic.c utils_matrix.c  \
						utils_parenthesis2.c utils_parenthesis.c  \
						utils_string2.c utils_string.c utils_tokencheck.c
UTILS = 				$(addprefix $(UTILS_DIR)/, $(UTILS_FILES))

#SECTION - Putting all together:
SRC = $(BONUS) $(BUILTINS) $(ENV) $(EXECUTION_MAIN) $(MEMORY) $(EXECUTION_PREP) $(UTILS)

SRC_DEBUG = $(DEBUG_DIR)/debug.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_DEBUG = $(addprefix $(OBJ_DIR)/, $(SRC_DEBUG:.c=.o))

FLAGS = -Wall -Werror -Wextra -lreadline -lhistory -g

LIBFT = ../Ssj_libft/libft.a
DEBUG_LIBFT = $(DEBUG_DIR)/debug_resources/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	cc -Wall -Werror -Wextra -g -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rcs $(NAME).a $(OBJ)

$(OBJ_DIR): 
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(BONUS_DIR)
	mkdir -p $(OBJ_DIR)/$(BUILT_DIR)
	mkdir -p $(OBJ_DIR)/$(DEBUG_DIR)
	mkdir -p $(OBJ_DIR)/$(ENV_DIR)
	mkdir -p $(OBJ_DIR)/$(EXEC_DIR)
	mkdir -p $(OBJ_DIR)/$(MEM_DIR)
	mkdir -p $(OBJ_DIR)/$(PREP_DIR)
	mkdir -p $(OBJ_DIR)/$(UTILS_DIR)

deb: $(OBJ_DIR) $(OBJ) $(OBJ_DEBUG)
	cc -D DEBUG=1 $(FLAGS) -fPIE $(OBJ_DEBUG) $(OBJ) $(DEBUG_LIBFT) -o exe.out

clean: frm
	rm -rf obj_executor/*.o *.out *.gdb *.supp
	rm -f debug_tools/*.out
	rm -rf obj_executor

fclean: clean
	rm -rf $(NAME).a
	rm -f $(DEBUG_DIR)/debug_resources/libft.a

re: fclean all

#frm = file remove
frm: 
	rm -f *.txt
	rm -f $(DEBUG_DIR)/debug_resources/bash_tests/*.txt

gdb: 
	$(MAKE) gdb_file -C debug_tools/

val: 
	$(MAKE) valgrind_file -C debug_tools/

#FIXME - Remove the following commands in the final project.
#Get a copy of my libft.a
debug_libft: 
	$(MAKE) all -C ../../Libft/
	cp ../../Libft/libft.a $(DEBUG_DIR)/debug_resources/
	$(MAKE) fclean -C ../../Libft/

#Get libft.a, compile the program, clear screen
start: debug_libft deb
	clear

#make re for debug
r: fclean start
	
#Remove useless files, return to root of the git, update git
git: fclean frm
	cd $(COMMON_CORE)
	git add .
	git commit -m "$(MSG)"
	git push

.PHONY: fclean re clean deb all