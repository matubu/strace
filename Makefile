NAME = ft_strace

SRCS = main.c syscall.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Ofast

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $^

$(NAME): $(OBJS)
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re