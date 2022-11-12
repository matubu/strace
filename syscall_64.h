#pragma once

#include "syscall.h"

const syscall_t syscalls_64[] = {
	[__NR_write] = {"write", {Long, Ptr, ULong, None}, Long},
	[__NR_read] = {"read", {Long, Ptr, ULong, None}, Long},
	[__NR_open] = {"open", {String, Long, None}, Long},
	[__NR_close] = {"close", {Long, None}, Long},
};