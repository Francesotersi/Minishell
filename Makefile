#–– Compiler settings
CC       = cc
CFLAGS   = -g -Wall -Werror -Wextra -I./Ssj_libft
LDFLAGS  = -lreadline -lhistory -lncurses

#–– Library
LIBFT_DIR = Ssj_libft
LIBFT     = $(LIBFT_DIR)/libft.a
PARS_DIR  = parsing

#–– Top‑level target
NAME     = minishell

#––	Suppression file
SUPP_FILE = $(shell pwd)/supp.supp

#–– All source files, with their relative paths
SRCS = \
  main.c \
  signals.c \
  set_signal.c \
  executor/bonus/bonus_cmd_sub.c \
  executor/bonus/bonus_cmd_utils.c \
  executor/bonus/bonus_cmd_utils_2.c \
  executor/bonus/bonus_parenthesis.c \
  executor/bonus/bonus_wildcards1.c \
  executor/bonus/bonus_wildcards2.c \
  executor/builtins/builtin_cd.c \
  executor/builtins/builtin_echo.c \
  executor/builtins/builtin_env.c \
  executor/builtins/builtin_exit.c \
  executor/builtins/builtin_export.c \
  executor/builtins/builtin_pwd.c \
  executor/builtins/builtin_unset.c \
  executor/env_management/environment.c \
  executor/env_management/environment2.c \
  executor/execution_main/error_message.c \
  executor/execution_main/execute.c \
  executor/execution_prep/get_commands_data.c \
  executor/execution_prep/get_file_data.c \
  executor/execution_prep/get_paths_data.c \
  executor/execution_prep/get_tokens.c \
  executor/utils/printf_fd.c \
  executor/utils/utils_count.c \
  executor/utils/utils_debug.c \
  executor/utils/utils_fds.c \
  executor/utils/utils_fds2.c \
  executor/utils/utils_generic.c \
  executor/utils/utils_heredoc.c \
  executor/utils/utils_matrix.c \
  executor/utils/utils_memory.c \
  executor/utils/utils_parenthesis2.c \
  executor/utils/utils_parenthesis.c \
  executor/utils/utils_string2.c \
  executor/utils/utils_string.c \
  executor/utils/utils_tokencheck.c \
  parsing/start_lexing.c \
  parsing/fill_struct.c \
  parsing/utils.c \
  parsing/struct_alloc.c \
  parsing/remove_quotes.c \
  parsing/define_token.c \
  parsing/define_token_2.c \
  parsing/expand_env.c \
  parsing/expand_env_2.c \
  parsing/utils_2.c \
  parsing/parenthesis.c \
  parsing/parser.c \
  parsing/expand_wildcard.c \
  parsing/expand_wildcard_2.c \
  parsing/parser_2.c \
  parsing/ambiguous_redir.c \

#–– Object files go under obj/, mirroring the tree
OBJ_DIR = obj
OBJS    = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

#–– phony targets
.PHONY: all clean fclean re libft

all: $(NAME)

#–– Link the final minishell
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $@

#–– Build libft (bonus) before anything else
$(LIBFT): 
	$(MAKE) bonus -C $(LIBFT_DIR)

#–– Single pattern rule for every .c → .o
#––   - mkdir -p $(dir $@) makes sure subdirs exist
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

supp: 
	$(MAKE) val -C executor/
	mv executor/v.supp .
	mv v.supp $(SUPP_FILE)

deb:
	$(MAKE) gdb -C executor/
	mv executor/a.gdb .

val: 
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --track-origins=yes -s --quiet --suppressions=$(SUPP_FILE) ./minishell

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

bonus: fclean $(NAME)

re: fclean all
