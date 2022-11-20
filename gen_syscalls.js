function getType(type) {
	type = type
		.replaceAll(/\B(const|__user)\B/g, "")
		.trim();

	if (type == 'void') {
		return 'None';
	}
	if (/^.*\*[a-zA-Z0-9_]*$/.test(type)) {
		return 'Ptr';
	}
	if (/\B(_?_?u32|_?_?u64|size_t|.*unsigned.*)\B/.test(type)) {
		return 'ULong';
	}
	if (/\B(_?_?u32|_?_?u64|size_t|.*unsigned.*)\B/.test(type)) {
		return 'Long';
	}

	return 'Long';
}

const missingMans = {
	'pselect6': `int pselect6(int nfds, fd_set *readfds, fd_set *writefds,
				fd_set *exceptfds, const struct timespec *timeout,
				const sigset_t *sigmask);`,
	'ugetrlimit': `int ugetrlimit(int resource, struct rlimit *rlim);`,
	'signalfd4': `int signalfd4(int fd, const sigset_t *mask, int flags);`,
	'eventfd2': `int eventfd2(unsigned int initval, int flags);`,
	'io_pgetevents': `
		int syscall(SYS_io_getevents, aio_context_t ctx_id,
					long min_nr, long nr, struct io_event *events,
					struct timespec *timeout);`,
	'rseq': `int rseq(struct rseq *rseq, uint32_t rseq_len, int flags, uint32_t sig);`,
	'set_mempolicy_home_node': `long set_mempolicy_home_node(unsigned long start, unsigned long len,
				 unsigned long home_node,
					 unsigned long flags);`,
	'futex_waitv': `int futex_waitv(struct futex_waitv *waiters, unsigned int nr_futexes,
				unsigned int flags, struct timespec *timeout, clockid_t clockid);`,
	'process_mrelease': `int process_mrelease(int pidfd, unsigned int flags);`,
	'memfd_secret': `int memfd_secret(unsigned int flags);`,
	'landlock_restrict_self': `int syscall(SYS_landlock_restrict_self, int ruleset_fd,
				uint32_t flags);`,
	'landlock_add_rule': `int syscall(SYS_landlock_add_rule, int ruleset_fd,
				enum landlock_rule_type rule_type,
				const void *rule_attr, uint32_t flags);`,
}

const syscallClass = Deno.args[0];

const unistdPath = `/usr/include/asm/unistd_${syscallClass}.h`;
const unistdFile = await Deno.readTextFile(unistdPath);

console.log('#include "syscall.h"');
console.log(`#include <asm/unistd_${syscallClass}.h>`);
console.log(`const syscall_info_t syscalls_${syscallClass}[] = {`);

async function run(cmd) {
	const process = Deno.run({
		cmd,
		stdout: 'piped',
		stderr: 'null',
	});

	const s = new TextDecoder().decode(await process.output());
	await process.status();
	return s;
}

for (const syscall of unistdFile.matchAll(/#define __NR_(\w+)\s+(\d+)/g)) {
	const syscallName = syscall[1];
	const syscallNameWithoutFlavor = syscallName
		.replace(/(64)?_?64$/, '')
		.replace(/_?32$/, '')
		.replace(/^_?new/, '')
		.replace(/^old(old)?|_old$/, '')
		.replace(/^rt_/, '');

	if (syscall) {
		const syscallMan = missingMans[syscallName]
						|| await run([ "/usr/bin/man", "2", syscallName ])
						|| await run([ "/usr/bin/man", "2", syscallNameWithoutFlavor ]);

		const syscallDeclarationRegex = 
			new RegExp(`(.*[ *])(?:(?:_|posix_)?${syscallNameWithoutFlavor}\\(|syscall\\(SYS_${syscallName},)([^)]*)\\);`, 'm')
		const syscallDeclaration = syscallMan.match(syscallDeclarationRegex);

		if (syscallDeclaration == null) {
			if (!syscallMan.includes('Unimplemented system calls.')) {
				console.error('\x1b[91mError\x1b[0m parsing', syscallName, syscallMan);
			}
			continue ;
		}

		const returnType = getType(syscallDeclaration[1]);
		const args = syscallDeclaration[2].split(',').map(getType);
		console.log(`\t[__NR_${syscallName}] = {"${syscallName}", {${args.join(', ')}}, ${returnType}},`);
	}
}

console.log("};")