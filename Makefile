NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c lexer.c lexer_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS)

fclean: clean
    rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re