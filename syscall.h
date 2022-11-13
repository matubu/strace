#pragma once

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/user.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/uio.h>
#include <elf.h>
#include <inttypes.h>
#include <ctype.h>

// https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
// https://www.systutorials.com/docs/linux/man/2-syscalls/

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
	// Env
}	data_type_t;

typedef struct {
	char			*name;
	data_type_t		arguments[6];
	data_type_t		return_type;
}	syscall_info_t;

#define pu64 "%" PRIu64
#define pi64 "%" PRId64

typedef uint32_t	reg32_t;
typedef uint64_t	reg64_t;
typedef int32_t		sreg32_t;
typedef int64_t		sreg64_t;
typedef reg64_t		reg_t;
typedef sreg64_t	sreg_t;

typedef struct __attribute__((__packed__)) {
	reg32_t ebx;
	reg32_t ecx;
	reg32_t edx;
	reg32_t esi;
	reg32_t edi;
	reg32_t ebp;
	reg32_t eax;
	reg32_t xds;
	reg32_t xes;
	reg32_t xfs;
	reg32_t xgs;
	reg32_t orig_eax;
	reg32_t eip;
	reg32_t xcs;
	reg32_t eflags;
	reg32_t esp;
	reg32_t xss;
}	regs32_t;

typedef struct __attribute__((__packed__)) {
	reg64_t r15;
	reg64_t r14;
	reg64_t r13;
	reg64_t r12;
	reg64_t rbp;
	reg64_t rbx;
	reg64_t r11;
	reg64_t r10;
	reg64_t r9;
	reg64_t r8;
	reg64_t rax;
	reg64_t rcx;
	reg64_t rdx;
	reg64_t rsi;
	reg64_t rdi;
	reg64_t orig_rax;
	reg64_t rip;
	reg64_t cs;
	reg64_t eflags;
	reg64_t rsp;
	reg64_t ss;
	reg64_t fs_base;
	reg64_t gs_base;
	reg64_t ds;
	reg64_t es;
	reg64_t fs;
	reg64_t gs;
}	regs64_t;

typedef union {
	regs32_t	regs32;
	regs64_t	regs64;
}	regs_t;

typedef struct {
	enum {
		ARCH_64,
		ARCH_32,
	}						arch;
	reg_t					syscall_id;
	const syscall_info_t	*syscall_info;
	reg_t					args[6];
	reg_t					ret;
	sreg_t					sret;
}	syscall_data_t;

void print_reg_data(data_type_t type, reg_t reg);

#define MAX_SYSCALLS 512

extern const syscall_info_t syscalls_32[MAX_SYSCALLS];
extern const syscall_info_t syscalls_64[MAX_SYSCALLS];