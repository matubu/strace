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

const syscallClass = Deno.args[0];

const unistdPath = `/usr/include/asm/unistd_${syscallClass}.h`;
const unistdFile = await Deno.readTextFile(unistdPath);

console.log('#include "syscall.h"');
console.log(`#include <asm/unistd_${syscallClass}.h>`);
console.log(`const syscall_info_t syscalls_${syscallClass}[] = {`);

for (const syscall of unistdFile.matchAll(/#define __NR_(\w+)\s+(\d+)/g)) {
	const syscallName = syscall[1];

	if (syscall) {
		const process = Deno.run({
			cmd: [ "/usr/bin/man", "2", syscallName ],
			stdout: 'piped',
			stderr: 'null',
		});

		const syscallMan = new TextDecoder().decode(await process.output());
		await process.status();

		const syscallDeclaration = syscallMan.match(
			new RegExp(`(.*[ *])${syscallName}\\(([^)]*)\\);`, 'm')
		);

		if (syscallDeclaration == null) {
			continue ;
		}

		const returnType = getType(syscallDeclaration[1]);
		const args = syscallDeclaration[2].split(',').map(getType);
		console.log(`\t[__NR_${syscallName}] = {"${syscallName}", {${args.join(', ')}}, ${returnType}},`);
	}
}

console.log("};")