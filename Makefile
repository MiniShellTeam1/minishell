# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g
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
EXECUTOR_DIR = $(SRC_DIR)/executor
BUILTINS_DIR = $(SRC_DIR)/builtins
ENV_DIR = $(SRC_DIR)/environment
ERROR_DIR = $(SRC_DIR)/error
DEBUG_DIR = $(SRC_DIR)/debug

# Source files
SRCS = \
	$(SRC_DIR)/main.c \
	$(FUNCTIONS_DIR)/functions_01.c \
	$(FUNCTIONS_DIR)/functions_02.c \
	$(FUNCTIONS_DIR)/functions_03.c \
	$(LEXER_DIR)/lexer.c \
	$(LEXER_DIR)/lexer_utils.c \
	$(PARSER_DIR)/parser.c \
	$(PARSER_DIR)/parser_utils.c \
	$(EXECUTOR_DIR)/executor.c \
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
	$(DEBUG_DIR)/debug.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Header files
HEADERS = \
	$(INCLUDE_DIR)/minishell.h \

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
