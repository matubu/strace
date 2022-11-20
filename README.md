# Strace
🐛 A debugging tool to trace syscalls and signal of a program

## TODO
 - Parsing arguments
 - Handle signals (sigprocmask)
 - Handle -c flag (count the syscall and their time to make a summary)
 - Fix bug missing last syscall return && test_1 double return for wait
 - Missing syscall ex: rseq