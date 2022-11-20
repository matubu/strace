#include "syscall.h"

typedef void (*data_type_printer)(reg_t reg);

void print_none(reg_t reg)
{
	(void)reg;
	printf("\x1b[90m?\x1b[0m");
}

// void _print_buf(char *s, size_t len) {
// 	printf("\x1b[92m\"");
// 	for (size_t i = 0; i < len; i++) {
// 		switch (s[i]) {
// 			case '\f':
// 				printf("\x1b[91m\\f\x1b[92m");
// 				break;
// 			case '\n':
// 				printf("\x1b[91m\\n\x1b[92m");
// 				break;
// 			case '\r':
// 				printf("\x1b[91m\\r\x1b[92m");
// 				break;
// 			case '\t':
// 				printf("\x1b[91m\\t\x1b[92m");
// 				break;
// 			case '\v':
// 				printf("\x1b[91m\\v\x1b[92m");
// 				break;
// 			default:
// 				if (isprint(s[i])) {
// 					printf("%c", s[i]);
// 				} else {
// 					printf("\x1b[91m\\x%02x\x1b[92m", s[i]);
// 				}
// 				break;
// 		}

// 	}
// 	printf("\"\x1b[0m");
// }

// void print_string(reg_t reg)
// {
// 	char *str = (char *)reg;
// 	_print_buf(str, strlen(str));
// }

void print_ptr(reg_t reg)
{
	printf("\x1b[93m%p\x1b[0m", (void *)reg.u);
}

void print_ulong(reg_t reg)
{
	printf("\x1b[93m" pu64 "\x1b[0m", reg.u);
}

void print_long(reg_t reg)
{
	printf("\x1b[93m" pu64 "\x1b[0m", reg.s);
}

// void print_argv(reg_t reg)
// {
// 	char **argv = (char **)reg;
// 	if (argv == NULL) {
// 		printf("\x1b[93mNULL\x1b[0m");
// 		return;
// 	}
// 	printf("[");
// 	for (size_t i = 0; argv[i]; i++) {
// 		if (i) {
// 			printf(", ");
// 		}
// 		_print_buf(argv[i], strlen(argv[i]));
// 	}
// 	printf("]");
// }

// void print_env(reg_t reg)
// {
// 	char **env = (char **)reg;
// 	if (env == NULL) {
// 		printf("\x1b[93mNULL\x1b[0m");
// 		return;
// 	}
// 	print_ptr(reg);
// 	size_t vars = 0;
// 	while (env[vars])
// 		++vars;
// 	printf(" \x1b[90m/* %zu vars */\x1b[0m", vars);
// }

data_type_printer data_type_printer_map[] = {
	[None]   = print_none,
	// [String] = print_string,
	[Ptr]    = print_ptr,
	[ULong]  = print_ulong,
	[Long]   = print_long,
	// [Argv]   = print_argv,
	// [Env]    = print_env,
};

void print_reg_data(data_type_t type, reg_t reg) {
	if (type > sizeof(data_type_printer_map) / sizeof(*data_type_printer_map))
		return ;
	data_type_printer_map[type](reg);
}