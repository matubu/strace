#include "errno_map.h"
#include "syscall.h"
#include "utils.h"

void usage() {
	printf("strace: must have PROG [ARGS]\n");
	exit(1);
}

// Child process
void setup_tracee() {
	if (ptrace(PTRACE_TRACEME, 0, NULL, NULL)) {
		syserr("ptrace");
	}

	kill(getpid(), SIGSTOP);
}

void print_syscall_pre(const syscall_data_t *data) {
	printf("\x1b[94m%s\x1b[0m(", data->syscall_info->name);
	for (int i = 0; i < 6; i++) {
		if (data->syscall_info->arguments[i] == None) {
			break;
		}
		if (i) {
			printf(", ");
		}
		print_reg_data(data->syscall_info->arguments[i], data->args[i]);
	}
	printf(")");
}

void print_syscall_post(const syscall_data_t *data) {
	// TODO read return type (ptr, str, ulong, int, none)
	printf(" = \x1b[93m" pi64 "\x1b[0m", data->sret);
	if (data->sret < 0 && -data->sret < MAX_ERRNO) {
		printf(" \x1b[90m%s\x1b[0m (\x1b[91m%s\x1b[0m)", errno_map[-data->sret], strerror(-data->sret));
	}
	printf("\n");
}

syscall_data_t get_syscall_data(struct iovec *iov) {
	syscall_data_t data;

	switch (iov->iov_len) {
		case sizeof(regs32_t): {
			regs32_t *regs32 = iov->iov_base;
			data.arch = ARCH_32;
			data.syscall_id = regs32->orig_eax;
			data.syscall_info = syscalls_32 + data.syscall_id;
			data.args[0] = regs32->ebx;
			data.args[1] = regs32->ecx;
			data.args[2] = regs32->edx;
			data.args[3] = regs32->esi;
			data.args[4] = regs32->edi;
			data.args[5] = regs32->ebp;
			data.ret = regs32->eax;
			data.sret = (sreg32_t)regs32->eax;
			return data;
		}
		case sizeof(regs64_t): {
			regs64_t *regs64 = iov->iov_base;
			data.arch = ARCH_64;
			data.syscall_id = regs64->orig_rax;
			data.syscall_info = syscalls_64 + data.syscall_id;
			data.args[0] = regs64->rdi;
			data.args[1] = regs64->rsi;
			data.args[2] = regs64->rdx;
			data.args[3] = regs64->r10;
			data.args[4] = regs64->r8;
			data.args[5] = regs64->r9;
			data.ret = regs64->rax;
			data.sret = regs64->rax;
			return data;
		}
		default: {
			syserr("get_syscall_data");
			exit(1);
		}
	}
}

// Parent process
void strace_trace(pid_t pid) {
	// TODO write strings for read and write ?
	// TODO sigprocmask & handle signals
	// TODO error message when invalid path and use PATH variable
	// TODO option -c to count syscalls
	// TODO fix double print and missing last syscall return value
	// ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACESYSGOOD);

	while (1) {
		int status;
		if (waitpid(pid, &status, 0) == -1) {
			perror("waitpid");
			exit(1);
		}

		if (WIFEXITED(status)) {
			printf("+++ exited with %d +++\n", WEXITSTATUS(status));
			break;
		}

		// Get the registers values
		regs_t regs;
		struct iovec iov = {
			.iov_base = &regs,
			.iov_len = sizeof(regs),
		};
		if (ptrace(PTRACE_GETREGSET, pid, NT_PRSTATUS, &iov) == -1) {
			syserr("ptrace getregs");
		}

		syscall_data_t data = get_syscall_data(&iov);

		if (data.syscall_id < MAX_SYSCALLS && data.syscall_info->name != NULL) {
			// https://stackoverflow.com/questions/52056385/after-attaching-to-process-how-to-check-whether-the-tracee-is-in-a-syscall
			if (data.sret == -ENOSYS) {
				print_syscall_pre(&data);
			} else {
				print_syscall_post(&data);
			}
			fflush(stdout);
		}

		// Continue until next syscall
		if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL) == -1) {
			syserr("ptrace syscall");
		}
	}
}

int main(int ac, char **av) {
	if (ac < 2) {
		usage();
	}

	char *path = find_path(av[1]);
	if (access(path, X_OK) == -1) {
		syserr("can't find program");
	}

	// Fork a child process
	pid_t pid = fork();
	if (pid == -1) {
		syserr("fork");
	}

	if (pid == 0) {
		setup_tracee();
		execvp(path, av + 1);
		syserr("execvp");
	}
	else {
		strace_trace(pid);
	}
}
