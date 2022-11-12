#include "syscall.h"

typedef void (*data_type_printer)(reg_t reg, regs_t *regs);

void print_none(reg_t reg, regs_t *regs)
{
	(void)reg;
	(void)regs;
	printf("\x1b[90m?\x1b[0m");
}

void print_string(reg_t reg, regs_t *regs)
{
	(void)regs;
	char *str = (char *)reg;
	printf("\x1b[92\"%s\"\x1b[0m", str);
}

void print_ptr(reg_t reg, regs_t *regs)
{
	(void)regs;
	printf("\x1b[93m%p\x1b[0m", (void *)reg);
}

void print_ulong(reg_t reg, regs_t *regs)
{
	(void)regs;
	printf("\x1b[93m%llu\x1b[0m", reg);
}

void print_long(reg_t reg, regs_t *regs)
{
	(void)regs;
	printf("\x1b[93m%lld\x1b[0m", reg);
}

data_type_printer data_type_printer_map[] = {
	[None]   = print_none,
	[String] = print_string,
	[Ptr]    = print_ptr,
	[ULong]  = print_ulong,
	[Long]   = print_long,
};

void print_reg_data(data_type_t type, reg_t reg, regs_t *regs) {
	if (type > sizeof(data_type_printer_map) / sizeof(*data_type_printer_map))
		return ;
	data_type_printer_map[type](reg, regs);
}