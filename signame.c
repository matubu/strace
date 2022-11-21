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
	[SIGIO] = "SIGIO",
	[SIGKILL] = "SIGKILL",
	[SIGPIPE] = "SIGPIPE",
	[SIGPROF] = "SIGPROF",
	[SIGPWR] = "SIGPWR",
	[SIGQUIT] = "SIGQUIT",
	[SIGSEGV] = "SIGSEGV",
	[SIGSTKFLT] = "SIGSTKFLT",
	[SIGSTOP] = "SIGSTOP",
	[SIGTSTP] = "SIGTSTP",
	[SIGSYS] = "SIGSYS",
	[SIGTERM] = "SIGTERM",
	[SIGTRAP] = "SIGTRAP",
	[SIGTTIN] = "SIGTTIN",
	[SIGTTOU] = "SIGTTOU",
	[SIGURG] = "SIGURG",
	[SIGUSR1] = "SIGUSR1",
	[SIGUSR2] = "SIGUSR2",
	[SIGVTALRM] = "SIGVTALRM",
	[SIGXCPU] = "SIGXCPU",
	[SIGXFSZ] = "SIGXFSZ",
	[SIGWINCH] = "SIGWINCH",
};

const char *get_signame(int sig) {
	if ((size_t)sig >= (sizeof(sigmap) / sizeof(sigmap[0])) || !sigmap[sig]) {
		return "UNKNOWN";
	}
	return sigmap[sig];
}