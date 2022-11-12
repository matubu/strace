#include <stdio.h>
#include <fcntl.h>

int main() {
	int fd = open("hello.c", O_RDONLY);
	printf("hello world %d\n", fd);
}