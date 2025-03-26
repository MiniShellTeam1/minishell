NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c lexer.c lexer_utils.c parser.c parser_utils.c
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(LIBFT):
    make -C libft

$(NAME): $(LIBFT) $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@ -Ilibft

clean:
    rm -f $(OBJS)
    make -C libft clean

fclean: clean
    rm -f $(NAME)
    make -C libft fclean

re: fclean all

.PHONY: all clean fclean re