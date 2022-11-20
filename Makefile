NAME = ft_strace

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=objects/%.o) objects/syscalls_32.o objects/syscalls_64.o

CFLAGS = -Wall -Wextra -Werror -Ofast

all: $(NAME)

syscalls_header:
	deno run --allow-read --allow-run gen_syscalls.js 32 > syscalls_32.c
	deno run --allow-read --allow-run gen_syscalls.js 64 > syscalls_64.c

objects/%.o: %.c
	mkdir -p objects
	gcc $(CFLAGS) -c -o $@ $^

$(NAME): $(OBJS)
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -rf objects

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re