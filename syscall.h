#pragma once

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/user.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

// https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/

typedef enum {
	None,
	String,
	Ptr,
	ULong,
	Long,
	// Buf,    // Use return value as buffer size
	// String for write
	// StringArray
	// ProtFlag,
	// MapFlag,
	// OFlag,
	// ModeT,
	// SigNum
	// Struct ?
}	data_type_t;

typedef struct {
	char			*name;
	data_type_t		arguments[6];
	data_type_t		return_type;
}	syscall_t;

typedef unsigned long long int				reg_t;
typedef long long int						sreg_t;
typedef struct user_regs_struct				regs_t;

void print_reg_data(data_type_t type, reg_t reg, regs_t *regs);

#define MAX_SYSCALLS 512

extern const syscall_t syscalls_32[MAX_SYSCALLS];
extern const syscall_t syscalls_64[MAX_SYSCALLS];