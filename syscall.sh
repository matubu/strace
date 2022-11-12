#!/bin/sh

if [ ! -d linux ]; then
	# Clone without history
	git clone --depth 1 git@github.com:torvalds/linux.git linux;
fi

cd linux

ag --multiline -ro --nobreak --nofilename '^SYSCALL_DEFINE\d\([^\)]+\)' \
	| tr '\n)' ' \n' \
	| tr -d '\t' \
	| sed 's/^\s//g' \
	| cut -c 17- \
	| awk -F, '{for(i=2;i<=12;++i)$i=$i?$i:"None"}{print "[__NR_"$1"] = {\""$1"\", {"$2", "$4", "$6", "$8", "$10", "$12"}, Long},"}' \
	| sed -r 's/const//g' \
	| sed -r 's/[^,]+\*/Ptr/g' \
	| sed -r 's/([^,]* )?(unsigned|size_t|_?_?u32)[^,]*/ULong/g' \
	| sed -r 's/[^,]*(int|ssize_t)[^,]*/ULong/g' \
# grep "#define " /usr/include/asm/unistd_64.h | cut -c 14-
# grep "#define " /usr/include/asm/unistd_32.h | cut -c 14-
