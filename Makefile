# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lreadline

# Project name
NAME = minishell

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
FUNCTIONS_DIR = $(SRC_DIR)/functions
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
EXPANSION_DIR = $(SRC_DIR)/expansion
EXECUTOR_DIR = $(SRC_DIR)/executor
BUILTINS_DIR = $(SRC_DIR)/builtins
ENV_DIR = $(SRC_DIR)/environment
ERROR_DIR = $(SRC_DIR)/error
DEBUG_DIR = $(SRC_DIR)/debug
SIGNAL_DIR = signal

# Source files
SRCS = \
	$(SRC_DIR)/main.c \
	$(FUNCTIONS_DIR)/functions_01.c \
	$(FUNCTIONS_DIR)/functions_01b.c \
	$(FUNCTIONS_DIR)/functions_02.c \
	$(FUNCTIONS_DIR)/functions_03.c \
	$(FUNCTIONS_DIR)/functions_04.c \
	$(LEXER_DIR)/lexer_init.c \
	$(LEXER_DIR)/lexer_main.c \
	$(LEXER_DIR)/lexer_utils.c \
	$(LEXER_DIR)/lexer_normal.c \
	$(LEXER_DIR)/lexer_quotes.c \
	$(LEXER_DIR)/lexer_word.c \
	$(LEXER_DIR)/lexer_operators.c \
	$(LEXER_DIR)/lexer_helpers.c \
	$(EXPANSION_DIR)/expand_main.c \
	$(EXPANSION_DIR)/expand_field_utils.c \
	$(EXPANSION_DIR)/expand_utils.c \
	$(EXPANSION_DIR)/expand_context.c \
	$(EXPANSION_DIR)/expand_vars.c \
	$(EXPANSION_DIR)/expand_quote_removal.c \
	$(EXPANSION_DIR)/expand_field_splitting.c \
	$(PARSER_DIR)/parser_init.c \
	$(PARSER_DIR)/parser_main.c \
	$(PARSER_DIR)/parser_tokens.c \
	$(PARSER_DIR)/parser_redirects.c \
	$(PARSER_DIR)/parser_utils.c \
	$(PARSER_DIR)/parser_commands.c \
	$(PARSER_DIR)/parser_utils_2.c \
	$(PARSER_DIR)/parser_input_priority.c \
	$(PARSER_DIR)/parser_arguments.c \
	$(EXECUTOR_DIR)/execution.c \
	$(EXECUTOR_DIR)/heredoc.c \
	$(EXECUTOR_DIR)/free.c \
	$(EXECUTOR_DIR)/execution_utils.c \
	$(BUILTINS_DIR)/cd.c \
	$(BUILTINS_DIR)/echo.c \
	$(BUILTINS_DIR)/env.c \
	$(BUILTINS_DIR)/exit.c \
	$(BUILTINS_DIR)/export.c \
	$(BUILTINS_DIR)/pwd.c \
	$(BUILTINS_DIR)/unset.c \
	$(ENV_DIR)/environment.c \
	$(ENV_DIR)/environment_utils.c \
	$(ERROR_DIR)/error.c \
	$(DEBUG_DIR)/debug.c \
	$(SIGNAL_DIR)/signal.c

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Header files
HEADERS = $(INCLUDE_DIR)/minishell.h

# Debug command
#debug: CFLAGS += -g -DDEBUG
#debug: clean $(NAME)
#	gdb --args ./$(NAME)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus debug