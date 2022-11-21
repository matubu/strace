#include "errno_map.h"
#include "syscall.h"
#include "utils.h"
#include "signame.h"

void usage() {
	printf("strace: must have PROG [ARGS]\n");
	exit(1);
}

void strace_sig_resetmask() {
	sigset_t set;
	sigemptyset(&set);
	sigprocmask(SIG_SETMASK, &set, NULL);
}

void strace_sig_block() {
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGHUP);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	sigaddset(&set, SIGPIPE);
	sigaddset(&set, SIGTERM);
	sigprocmask(SIG_BLOCK, &set, NULL);
}

// Parent process
void setup_tracer(pid_t pid) {
	if (ptrace(PTRACE_SEIZE, pid, NULL, NULL) == -1) {
		syserr("ptrace");
	}

	strace_sig_resetmask();
	int status;
	if (waitpid(pid, &status, 0) < 0) {
		syserr("waitpid");
	}
	strace_sig_block();

	if (ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACESYSGOOD) < 0) {
		syserr("ptrace setoptions");
	}
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

void print_syscall_error(const syscall_data_t *data) {
	if (data->syscall_info->return_type == Ptr) {
		if (data->ret.s == -1 || data->ret.u == 0) {
			printf(" \x1b[91mError\x1b[0m");
		}
		return ;
	}
	if (data->ret.s < 0) {
		printf(" \x1b[90m%s\x1b[0m (\x1b[91m%s\x1b[0m)", errno_map[-data->ret.s], strerror(-data->ret.s));
	}
}

void print_syscall_post(const syscall_data_t *data) {
	printf(" = ");
	print_reg_data(data->syscall_info->return_type, data->ret);
	print_syscall_error(data);
	printf("\n");
}

reg_t reg64_to_reg(reg64_t reg64) {
	return (reg_t) {
		.u = reg64,
		.s = (sreg64_t)reg64,
	};
}

reg_t reg32_to_reg(reg32_t reg32) {
	return (reg_t) {
		.u = reg32,
		.s = (sreg32_t)reg32,
	};
}

syscall_data_t get_syscall_data(struct iovec *iov) {
	syscall_data_t data;

	switch (iov->iov_len) {
		case sizeof(regs32_t): {
			regs32_t *regs32 = iov->iov_base;
			data.arch = ARCH_32;
			data.syscall_id = reg32_to_reg(regs32->orig_eax);
			data.syscall_info = syscalls_32 + data.syscall_id.u;
			data.args[0] = reg32_to_reg(regs32->ebx);
			data.args[1] = reg32_to_reg(regs32->ecx);
			data.args[2] = reg32_to_reg(regs32->edx);
			data.args[3] = reg32_to_reg(regs32->esi);
			data.args[4] = reg32_to_reg(regs32->edi);
			data.args[5] = reg32_to_reg(regs32->ebp);
			data.ret = reg32_to_reg(regs32->eax);
			return data;
		}
		case sizeof(regs64_t): {
			regs64_t *regs64 = iov->iov_base;
			data.arch = ARCH_64;
			data.syscall_id = reg64_to_reg(regs64->orig_rax);
			data.syscall_info = syscalls_64 + data.syscall_id.u;
			data.args[0] = reg64_to_reg(regs64->rdi);
			data.args[1] = reg64_to_reg(regs64->rsi);
			data.args[2] = reg64_to_reg(regs64->rdx);
			data.args[3] = reg64_to_reg(regs64->r10);
			data.args[4] = reg64_to_reg(regs64->r8);
			data.args[5] = reg64_to_reg(regs64->r9);
			data.ret = reg64_to_reg(regs64->rax);
			return data;
		}
		default: {
			syserr("get_syscall_data");
			exit(1);
		}
	}
}

void strace_handle_syscall(pid_t pid) {
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

	if (data.syscall_id.u < MAX_SYSCALLS && data.syscall_info->name != NULL) {
		// https://stackoverflow.com/questions/52056385/after-attaching-to-process-how-to-check-whether-the-tracee-is-in-a-syscall
		if (data.ret.s == -ENOSYS) {
			print_syscall_pre(&data);
		} else {
			print_syscall_post(&data);
		}
		fflush(stdout);
	}
	else if (data.ret.s == -ENOSYS) {
		printf("syscall(" pu64 ")", data.syscall_id.u);
	} else {
		printf(" => " pi64 "\n", data.ret.s);
	}
}

void strace_handle_sigstopped(pid_t pid) {
	siginfo_t		siginfo;

	ptrace(PTRACE_GETSIGINFO, pid, NULL, &siginfo);
	printf("--- \x1b[91m%s\x1b[0m {\
 si_signo=\x1b[91m%s\x1b[0m,\
 si_code=\x1b[93m%d\x1b[0m,\
 si_pid=\x1b[93m%d\x1b[0m,\
 si_uid=\x1b[93m%d\x1b[0m,\
 si_status=\x1b[93m%d\x1b[0m,\
 si_utime=\x1b[93m%lu\x1b[0m,\
 si_stime=\x1b[93m%ld\x1b[0m,\
 si_addr=\x1b[93m%p\x1b[0m\
} ---\n",
		get_signame(siginfo.si_signo),
		get_signame(siginfo.si_signo),
		siginfo.si_code,
		siginfo.si_pid,
		siginfo.si_uid,
		siginfo.si_status,
		siginfo.si_utime,
		siginfo.si_stime,
		siginfo.si_addr
	);
	if (siginfo.si_signo == SIGSEGV) {
		printf("+++ killed by SIGSEGV (core dumped) +++\n");
		raise(SIGSEGV);
	}
}

// Parent process
void strace_trace(pid_t pid) {
	while (1) {
		// Continue until next syscall
		if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL) == -1) {
			syserr("ptrace syscall");
		}

		int status;
		strace_sig_resetmask();
		if (waitpid(pid, &status, 0) == -1) {
			perror("waitpid");
			exit(1);
		}
		strace_sig_block();

		if (WIFEXITED(status)) {
			printf(" = \x1b[90m?\x1b[0m\n");
			printf("+++ exited with %d +++\n", WEXITSTATUS(status));
			break;
		}

		if (WIFSIGNALED(status)) {
			printf(" = \x1b[90m?\x1b[0m\n");
			printf("+++ killed by %s +++\n", get_signame(WTERMSIG(status)));
			break;
		}

		if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80) {
			strace_handle_syscall(pid);
		} else {
			strace_handle_sigstopped(pid);
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
		//`Child process
		raise(SIGSTOP);
		execvp(path, av + 1);
		syserr("execvp");
	}
	else {
		// Parent process
		setup_tracer(pid);
		strace_trace(pid);
	}
}
