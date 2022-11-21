# Strace
🐛 A debugging tool to trace syscalls and signal of a program

## TODO
 - Handle -c flag (count the syscall and their time to make a summary)
 - Fix clanky fix for last syscall return value missing
 - ptrace regs wrong value ex: mmap -1
 - strace cat Ctrl-C

## Resources
 - https://abda.nl/posts/understanding-ptrace/
 - https://stackoverflow.com/questions/52056385/after-attaching-to-process-how-to-check-whether-the-tracee-is-in-a-syscall
 - https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
 - https://www.systutorials.com/docs/linux/man/2-syscalls/