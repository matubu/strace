NAME = ft_strace

SRCS = main.c syscall.c errors.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Ofast

all: $(NAME)

syscalls_32.c:
	./gen_syscalls.sh 32 > syscalls_32.c
syscalls_64.c:
	./gen_syscalls.sh 64 > syscalls_64.c

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $^

$(NAME): syscalls_32.c syscalls_64.c $(OBJS)
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
	rm -rf syscalls_32.c syscalls_64.c

re: fclean all

.PHONY: all clean fclean re