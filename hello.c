#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
	int fd = open("hello.c", O_RDONLY);
	printf("hello world %d\n", fd);
	mmap(NULL, 0, 0, 0, fd, 0);
	execve("/bin/ls", NULL, NULL);
}