#include <signal.h>

const char *sigmap[] = {
	[SIGABRT] = "SIGABRT",
	[SIGALRM] = "SIGALRM",
	[SIGBUS] = "SIGBUS",
	[SIGCHLD] = "SIGCHLD",
	[SIGCONT] = "SIGCONT",
	[SIGFPE] = "SIGFPE",
	[SIGHUP] = "SIGHUP",
	[SIGILL] = "SIGILL",
	[SIGINT] = "SIGINT",
	[SIGKILL] = "SIGKILL",
	[SIGPIPE] = "SIGPIPE",
	[SIGPROF] = "SIGPROF",
	[SIGQUIT] = "SIGQUIT",
	[SIGSEGV] = "SIGSEGV",
	[SIGSTOP] = "SIGSTOP",
	[SIGTSTP] = "SIGTSTP",
	[SIGTERM] = "SIGTERM",
	[SIGTRAP] = "SIGTRAP",
	[SIGTTIN] = "SIGTTIN",
	[SIGTTOU] = "SIGTTOU",
	[SIGUSR1] = "SIGUSR1",
	[SIGUSR2] = "SIGUSR2",
};

const char *get_signame(int sig) {
	if ((size_t)sig >= (sizeof(sigmap) / sizeof(sigmap[0])) || !sigmap[sig]) {
		return "UNKNOWN";
	}
	return sigmap[sig];
}