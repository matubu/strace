#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define syserr(msg) { \
	perror("ft_strace: " msg); \
	exit(1); \
}

char *find_path(char *cmd);