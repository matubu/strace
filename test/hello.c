#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int ac, char **av) {
	if (av[0][0] == '\0') {
		while (1) {
			write(1, "test\n", 5);
			sleep(1);
		}
		return 1;
	}
	int fd = open("hello.c", O_RDONLY);
	int fd2 = open("ergergergerg", O_RDONLY);
	printf("%p\n", mmap(NULL, 0, 0, 0, fd, 0));
	execve(av[0], NULL, NULL);
}