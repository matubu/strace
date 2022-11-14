#!/bin/sh

# TODO missing syscalls ?

if [ ! -d linux ]; then
	# Clone without history
	git clone --depth 1 git@github.com:torvalds/linux.git linux > /dev/null;
fi

cd linux

echo "#include \"syscall.h\""
echo "#include <asm/unistd_$1.h>"
echo "const syscall_info_t syscalls_$1[] = {"

ag --multiline -ro --nobreak --nofilename '^SYSCALL_DEFINE\d\([^\)]+\)' \
	| tr '\n)' ' \n' \
	| tr -d '\t' \
	| sed 's/^\s//g' \
	| cut -c 17- \
	| awk -F, '
	function replace(s, name) {
		gsub(/const|__user/, "", s);
		# if (!(name ~ /buf/)) {
		# 	gsub(/^\s*char\s*\*\s*$/, "String", s);
		# }
		# if (name ~ /argv/) {
		# 	gsub(/^\s*char\s*\*\s*\*\s*$/, "Argv", s);
		# }
		# if (name ~ /env/) {
		# 	gsub(/^\s*char\s*\*\s*\*\s*$/, "Env", s);
		# }
		gsub(/.*\*/, "Ptr", s);
		gsub(/_?_?u32|_?_?u64|size_t|.*unsigned.*/, "ULong", s);
		gsub(/.*(_?_?s32|_?_?s64|int|ssize_t|long).*/, "ULong", s);
		gsub(/enum\s.*/, "ULong", s);
		gsub(/.*_t$/, "Long", s);
		return s;
	}
	{
		for (i = 2; i <= 12; i += 2) {
			j = i + 1;
			$i = $i ? replace($i, $j) : "None"
		}
		if (system("grep -e \"\\s__NR_"$1"\\s\" /usr/include/asm/unistd_'$1'.h > /dev/null") == 0)
			print "[__NR_"$1"] = {\""$1"\", {"$2", "$4", "$6", "$8", "$10", "$12"}, Long},"
	}
	' \
	| sort -u --field-separator== -k1,1

echo "};"

# grep "#define __NR_" /usr/include/asm/unistd_64.h | awk '{ print $2 }' | wc
# grep "#define " /usr/include/asm/unistd_32.h | cut -c 14-
