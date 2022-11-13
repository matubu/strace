#include "syscall.h"

void usage() {
	printf("strace: must have PROG [ARGS]\n");
	exit(1);
}

void syserr(char *msg) {
	perror(msg);
	exit(1);
}

// Child process
void strace_exec(char **args) {
	if (ptrace(PTRACE_TRACEME, 0, NULL, NULL)) {
		syserr("ptrace");
	}

	execvp(args[0], args);
	syserr("execvp");
}

void print_syscall_pre(regs_t *regs) {
	int syscall_id = regs->orig_rax;
	reg_t args[6] = {
		regs->rdi,
		regs->rsi,
		regs->rdx,
		regs->r10,
		regs->r8,
		regs->r9,
	};

	const syscall_t *syscall = syscalls_64 + syscall_id;
	if (syscall_id > (int)(sizeof(syscalls_64) / sizeof(*syscalls_64)) || syscall->name == NULL) {
		printf("syscall %d(%lld, %lld, %lld, %lld, %lld, %lld)", syscall_id, args[0], args[1], args[2], args[3], args[4], args[5]);
		return ;
	}

	printf("\x1b[94m%s\x1b[0m(", syscall->name);
	for (int i = 0; i < 6; i++) {
		if (syscall->arguments[i] == None) {
			break;
		}
		if (i) {
			printf(", ");
		}
		print_reg_data(syscall->arguments[i], args[i], regs);
	}
	printf(")");
}

void print_syscall_post(regs_t *regs) {
	sreg_t ret = regs->rax;

	// TODO read return type
	if (ret < 0) {
		printf(" = \x1b[93m-1\x1b[0m \x1b[91merrno %lld\x1b[0m\n", -ret);
	} else {
		printf(" = \x1b[93m%lld\x1b[0m\n", ret);
	}
}

// Parent process
void strace_trace(pid_t pid) {
	// TODO sigprocmask

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
		if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) == -1) {
			syserr("ptrace getregs");
		}

		// https://stackoverflow.com/questions/52056385/after-attaching-to-process-how-to-check-whether-the-tracee-is-in-a-syscall
		if ((sreg_t)regs.rax == -ENOSYS) {
			print_syscall_pre(&regs);
		} else {
			// Print the syscall name and arguments
			print_syscall_post(&regs);
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

	// Fork a child process
	pid_t pid = fork();
	if (pid == -1) {
		syserr("fork");
	}

	if (pid == 0) {
		strace_exec(av + 1);
	}
	else {
		strace_trace(pid);
	}
}