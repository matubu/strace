#include "syscall.h"
#include <asm/unistd_64.h>
const syscall_info_t syscalls_64[] = {
	[__NR_read] = {"read", {Long, Ptr, Long}, Long},
	[__NR_write] = {"write", {Long, Ptr, Long}, Long},
	[__NR_open] = {"open", {Ptr, Long}, Long},
	[__NR_close] = {"close", {Long}, Long},
	[__NR_stat] = {"stat", {Long, Long}, Long},
	[__NR_fstat] = {"fstat", {Long, Ptr}, Long},
	[__NR_lstat] = {"lstat", {Long, Long}, Long},
	[__NR_poll] = {"poll", {Ptr, Long, Long}, Long},
	[__NR_lseek] = {"lseek", {Long, Long, Long}, Long},
	[__NR_mmap] = {"mmap", {Ptr, Long, Long, Long, Long, Long}, Ptr},
	[__NR_mprotect] = {"mprotect", {Ptr, Long, Long}, Long},
	[__NR_munmap] = {"munmap", {Ptr, Long}, Long},
	[__NR_brk] = {"brk", {Ptr}, Long},
	[__NR_ioctl] = {"ioctl", {Long, Long, Long}, Long},
	[__NR_readv] = {"readv", {Long, Ptr, Long}, Long},
	[__NR_writev] = {"writev", {Long, Ptr, Long}, Long},
	[__NR_access] = {"access", {Ptr, Long}, Long},
	[__NR_pipe] = {"pipe", {Long}, Long},
	[__NR_select] = {"select", {Long, Long, Long, Long, Long}, Long},
	[__NR_sched_yield] = {"sched_yield", {None}, Long},
	[__NR_mremap] = {"mremap", {Ptr, Long, Long, Long, Long}, Ptr},
	[__NR_msync] = {"msync", {Ptr, Long, Long}, Long},
	[__NR_mincore] = {"mincore", {Ptr, Long, Ptr}, Long},
	[__NR_madvise] = {"madvise", {Ptr, Long, Long}, Long},
	[__NR_shmget] = {"shmget", {Long, Long, Long}, Long},
	[__NR_shmat] = {"shmat", {Long, Ptr, Long}, Ptr},
	[__NR_shmctl] = {"shmctl", {Long, Long, Ptr}, Long},
	[__NR_dup] = {"dup", {Long}, Long},
	[__NR_dup2] = {"dup2", {Long, Long}, Long},
	[__NR_pause] = {"pause", {None}, Long},
	[__NR_nanosleep] = {"nanosleep", {Ptr, Ptr}, Long},
	[__NR_getitimer] = {"getitimer", {Long, Ptr}, Long},
	[__NR_alarm] = {"alarm", {Long}, Long},
	[__NR_setitimer] = {"setitimer", {Long, Long, Long}, Long},
	[__NR_getpid] = {"getpid", {None}, Long},
	[__NR_sendfile] = {"sendfile", {Long, Long, Ptr, Long}, Long},
	[__NR_socket] = {"socket", {Long, Long, Long}, Long},
	[__NR_connect] = {"connect", {Long, Ptr, Long}, Long},
	[__NR_accept] = {"accept", {Long, Long, Long}, Long},
	[__NR_sendto] = {"sendto", {Long, Ptr, Long, Long, Ptr, Long}, Long},
	[__NR_recvfrom] = {"recvfrom", {Long, Long, Long, Long, Long, Long}, Long},
	[__NR_sendmsg] = {"sendmsg", {Long, Ptr, Long}, Long},
	[__NR_recvmsg] = {"recvmsg", {Long, Ptr, Long}, Long},
	[__NR_shutdown] = {"shutdown", {Long, Long}, Long},
	[__NR_bind] = {"bind", {Long, Ptr, Long}, Long},
	[__NR_listen] = {"listen", {Long, Long}, Long},
	[__NR_getsockname] = {"getsockname", {Long, Long, Long}, Long},
	[__NR_getpeername] = {"getpeername", {Long, Long, Long}, Long},
	[__NR_socketpair] = {"socketpair", {Long, Long, Long, Long}, Long},
	[__NR_setsockopt] = {"setsockopt", {Long, Long, Long, Ptr, Long}, Long},
	[__NR_getsockopt] = {"getsockopt", {Long, Long, Long, Long, Long}, Long},
	[__NR_clone] = {"clone", {Long, Ptr, Ptr, Ptr, Long}, Long},
	[__NR_fork] = {"fork", {None}, Long},
	[__NR_vfork] = {"vfork", {None}, Long},
	[__NR_execve] = {"execve", {Ptr, Long, Long}, Long},
	[__NR_wait4] = {"wait4", {Long, Ptr, Long, Ptr}, Long},
	[__NR_kill] = {"kill", {Long, Long}, Long},
	[__NR_uname] = {"uname", {Ptr}, Long},
	[__NR_semget] = {"semget", {Long, Long, Long}, Long},
	[__NR_semop] = {"semop", {Long, Ptr, Long}, Long},
	[__NR_semctl] = {"semctl", {Long, Long, Long, Long}, Long},
	[__NR_shmdt] = {"shmdt", {Ptr}, Long},
	[__NR_msgget] = {"msgget", {Long, Long}, Long},
	[__NR_msgsnd] = {"msgsnd", {Long, Ptr, Long, Long}, Long},
	[__NR_msgrcv] = {"msgrcv", {Long, Ptr, Long, Long, Long}, Long},
	[__NR_msgctl] = {"msgctl", {Long, Long, Ptr}, Long},
	[__NR_fcntl] = {"fcntl", {Long, Long, Long}, Long},
	[__NR_flock] = {"flock", {Long, Long}, Long},
	[__NR_fsync] = {"fsync", {Long}, Long},
	[__NR_fdatasync] = {"fdatasync", {Long}, Long},
	[__NR_truncate] = {"truncate", {Ptr, Long}, Long},
	[__NR_ftruncate] = {"ftruncate", {Long, Long}, Long},
	[__NR_getdents] = {"getdents", {Long}, Long},
	[__NR_getcwd] = {"getcwd", {Ptr, Long}, Ptr},
	[__NR_chdir] = {"chdir", {Ptr}, Long},
	[__NR_fchdir] = {"fchdir", {Long}, Long},
	[__NR_rename] = {"rename", {Ptr, Ptr}, Long},
	[__NR_mkdir] = {"mkdir", {Ptr, Long}, Long},
	[__NR_rmdir] = {"rmdir", {Ptr}, Long},
	[__NR_creat] = {"creat", {Ptr, Long}, Long},
	[__NR_link] = {"link", {Ptr, Ptr}, Long},
	[__NR_unlink] = {"unlink", {Ptr}, Long},
	[__NR_symlink] = {"symlink", {Ptr, Ptr}, Long},
	[__NR_readlink] = {"readlink", {Long, Long, Long}, Long},
	[__NR_chmod] = {"chmod", {Ptr, Long}, Long},
	[__NR_fchmod] = {"fchmod", {Long, Long}, Long},
	[__NR_chown] = {"chown", {Ptr, Long, Long}, Long},
	[__NR_fchown] = {"fchown", {Long, Long, Long}, Long},
	[__NR_lchown] = {"lchown", {Ptr, Long, Long}, Long},
	[__NR_umask] = {"umask", {Long}, Long},
	[__NR_gettimeofday] = {"gettimeofday", {Long, Long}, Long},
	[__NR_getrlimit] = {"getrlimit", {Long, Ptr}, Long},
	[__NR_getrusage] = {"getrusage", {Long, Ptr}, Long},
	[__NR_sysinfo] = {"sysinfo", {Ptr}, Long},
	[__NR_times] = {"times", {Ptr}, Long},
	[__NR_ptrace] = {"ptrace", {Long, Long, Ptr, Ptr}, Long},
	[__NR_getuid] = {"getuid", {None}, Long},
	[__NR_getgid] = {"getgid", {None}, Long},
	[__NR_setuid] = {"setuid", {Long}, Long},
	[__NR_setgid] = {"setgid", {Long}, Long},
	[__NR_geteuid] = {"geteuid", {None}, Long},
	[__NR_getegid] = {"getegid", {None}, Long},
	[__NR_setpgid] = {"setpgid", {Long, Long}, Long},
	[__NR_getppid] = {"getppid", {None}, Long},
	[__NR_getpgrp] = {"getpgrp", {None}, Long},
	[__NR_setsid] = {"setsid", {None}, Long},
	[__NR_setreuid] = {"setreuid", {Long, Long}, Long},
	[__NR_setregid] = {"setregid", {Long, Long}, Long},
	[__NR_getgroups] = {"getgroups", {Long, Long}, Long},
	[__NR_setgroups] = {"setgroups", {Long, Ptr}, Long},
	[__NR_setresuid] = {"setresuid", {Long, Long, Long}, Long},
	[__NR_getresuid] = {"getresuid", {Ptr, Ptr, Ptr}, Long},
	[__NR_setresgid] = {"setresgid", {Long, Long, Long}, Long},
	[__NR_getresgid] = {"getresgid", {Ptr, Ptr, Ptr}, Long},
	[__NR_getpgid] = {"getpgid", {Long}, Long},
	[__NR_setfsuid] = {"setfsuid", {Long}, Long},
	[__NR_setfsgid] = {"setfsgid", {Long}, Long},
	[__NR_getsid] = {"getsid", {Long}, Long},
	[__NR_sigaltstack] = {"sigaltstack", {Long, Long}, Long},
	[__NR_utime] = {"utime", {Ptr, Ptr}, Long},
	[__NR_mknod] = {"mknod", {Ptr, Long, Long}, Long},
	[__NR_uselib] = {"uselib", {Ptr}, Long},
	[__NR_personality] = {"personality", {Long}, Long},
	[__NR_ustat] = {"ustat", {Long, Ptr}, Long},
	[__NR_statfs] = {"statfs", {Ptr, Ptr}, Long},
	[__NR_fstatfs] = {"fstatfs", {Long, Ptr}, Long},
	[__NR_sysfs] = {"sysfs", {Long, Ptr}, Long},
	[__NR_getpriority] = {"getpriority", {Long, Long}, Long},
	[__NR_setpriority] = {"setpriority", {Long, Long, Long}, Long},
	[__NR_sched_setparam] = {"sched_setparam", {Long, Ptr}, Long},
	[__NR_sched_getparam] = {"sched_getparam", {Long, Ptr}, Long},
	[__NR_sched_setscheduler] = {"sched_setscheduler", {Long, Long, Ptr}, Long},
	[__NR_sched_getscheduler] = {"sched_getscheduler", {Long}, Long},
	[__NR_sched_get_priority_max] = {"sched_get_priority_max", {Long}, Long},
	[__NR_sched_get_priority_min] = {"sched_get_priority_min", {Long}, Long},
	[__NR_sched_rr_get_interval] = {"sched_rr_get_interval", {Long, Ptr}, Long},
	[__NR_mlock] = {"mlock", {Ptr, Long}, Long},
	[__NR_munlock] = {"munlock", {Ptr, Long}, Long},
	[__NR_mlockall] = {"mlockall", {Long}, Long},
	[__NR_munlockall] = {"munlockall", {None}, Long},
	[__NR_vhangup] = {"vhangup", {None}, Long},
	[__NR_pivot_root] = {"pivot_root", {Long, Long}, Long},
	[__NR__sysctl] = {"_sysctl", {Ptr}, Long},
	[__NR_prctl] = {"prctl", {Long, Long, Long, Long, Long}, Long},
	[__NR_adjtimex] = {"adjtimex", {Ptr}, Long},
	[__NR_setrlimit] = {"setrlimit", {Long, Ptr}, Long},
	[__NR_chroot] = {"chroot", {Ptr}, Long},
	[__NR_sync] = {"sync", {None}, None},
	[__NR_acct] = {"acct", {Ptr}, Long},
	[__NR_settimeofday] = {"settimeofday", {Ptr, Ptr}, Long},
	[__NR_mount] = {"mount", {Ptr, Ptr, Ptr, Long, Ptr}, Long},
	[__NR_umount2] = {"umount2", {Ptr, Long}, Long},
	[__NR_swapon] = {"swapon", {Ptr, Long}, Long},
	[__NR_swapoff] = {"swapoff", {Ptr}, Long},
	[__NR_reboot] = {"reboot", {Long}, Long},
	[__NR_sethostname] = {"sethostname", {Ptr, Long}, Long},
	[__NR_setdomainname] = {"setdomainname", {Ptr, Long}, Long},
	[__NR_iopl] = {"iopl", {Long}, Long},
	[__NR_ioperm] = {"ioperm", {Long, Long, Long}, Long},
	[__NR_create_module] = {"create_module", {Ptr, Long}, Long},
	[__NR_init_module] = {"init_module", {Ptr, Ptr}, Long},
	[__NR_delete_module] = {"delete_module", {Ptr}, Long},
	[__NR_get_kernel_syms] = {"get_kernel_syms", {Ptr}, Long},
	[__NR_query_module] = {"query_module", {Ptr, Long, Ptr, Long, Ptr}, Long},
	[__NR_quotactl] = {"quotactl", {Long, Ptr, Long, Long}, Long},
	[__NR_nfsservctl] = {"nfsservctl", {Long, Ptr, Ptr}, Long},
	[__NR_gettid] = {"gettid", {None}, Long},
	[__NR_readahead] = {"readahead", {Long, Long, Long}, Long},
	[__NR_setxattr] = {"setxattr", {Ptr, Ptr, Ptr, Long, Long}, Long},
	[__NR_lsetxattr] = {"lsetxattr", {Ptr, Ptr, Ptr, Long, Long}, Long},
	[__NR_fsetxattr] = {"fsetxattr", {Long, Ptr, Ptr, Long, Long}, Long},
	[__NR_getxattr] = {"getxattr", {Ptr, Ptr, Ptr, Long}, Long},
	[__NR_lgetxattr] = {"lgetxattr", {Ptr, Ptr, Ptr, Long}, Long},
	[__NR_fgetxattr] = {"fgetxattr", {Long, Ptr, Ptr, Long}, Long},
	[__NR_listxattr] = {"listxattr", {Ptr, Ptr, Long}, Long},
	[__NR_llistxattr] = {"llistxattr", {Ptr, Ptr, Long}, Long},
	[__NR_flistxattr] = {"flistxattr", {Long, Ptr, Long}, Long},
	[__NR_removexattr] = {"removexattr", {Ptr, Ptr}, Long},
	[__NR_lremovexattr] = {"lremovexattr", {Ptr, Ptr}, Long},
	[__NR_fremovexattr] = {"fremovexattr", {Long, Ptr}, Long},
	[__NR_time] = {"time", {Ptr}, Long},
	[__NR_futex] = {"futex", {Long, Long, Long, Long, Long, Long}, Long},
	[__NR_sched_setaffinity] = {"sched_setaffinity", {Long, Long, Ptr}, Long},
	[__NR_sched_getaffinity] = {"sched_getaffinity", {Long, Long, Ptr}, Long},
	[__NR_io_setup] = {"io_setup", {Long, Ptr}, Long},
	[__NR_io_submit] = {"io_submit", {Long, Long, Ptr}, Long},
	[__NR_epoll_create] = {"epoll_create", {Long}, Long},
	[__NR_remap_file_pages] = {"remap_file_pages", {Ptr, Long, Long, Long, Long}, Long},
	[__NR_getdents64] = {"getdents64", {Long, Ptr, Long}, Long},
	[__NR_restart_syscall] = {"restart_syscall", {None}, Long},
	[__NR_semtimedop] = {"semtimedop", {Long, Ptr, Long, Ptr}, Long},
	[__NR_timer_create] = {"timer_create", {Long, Long, Long}, Long},
	[__NR_timer_settime] = {"timer_settime", {Long, Long, Long, Long}, Long},
	[__NR_timer_gettime] = {"timer_gettime", {Long, Ptr}, Long},
	[__NR_timer_getoverrun] = {"timer_getoverrun", {Long}, Long},
	[__NR_timer_delete] = {"timer_delete", {Long}, Long},
	[__NR_clock_settime] = {"clock_settime", {Long, Ptr}, Long},
	[__NR_clock_gettime] = {"clock_gettime", {Long, Ptr}, Long},
	[__NR_clock_getres] = {"clock_getres", {Long, Ptr}, Long},
	[__NR_clock_nanosleep] = {"clock_nanosleep", {Long, Long, Ptr, Ptr}, Long},
	[__NR_epoll_wait] = {"epoll_wait", {Long, Ptr, Long, Long}, Long},
	[__NR_epoll_ctl] = {"epoll_ctl", {Long, Long, Long, Ptr}, Long},
	[__NR_tgkill] = {"tgkill", {Long, Long, Long}, Long},
	[__NR_utimes] = {"utimes", {Ptr, Long}, Long},
	[__NR_mbind] = {"mbind", {Ptr, Long, Long, Ptr, Long, Long}, Long},
	[__NR_set_mempolicy] = {"set_mempolicy", {Long, Ptr, Long}, Long},
	[__NR_get_mempolicy] = {"get_mempolicy", {Ptr, Ptr, Long, Ptr, Long}, Long},
	[__NR_mq_open] = {"mq_open", {Ptr, Long}, Long},
	[__NR_mq_unlink] = {"mq_unlink", {Ptr}, Long},
	[__NR_mq_timedsend] = {"mq_timedsend", {Long, Ptr, Long, Long, Ptr}, Long},
	[__NR_mq_timedreceive] = {"mq_timedreceive", {Long, Long, Long, Long, Long}, Long},
	[__NR_mq_notify] = {"mq_notify", {Long, Ptr}, Long},
	[__NR_waitid] = {"waitid", {Long, Long, Ptr, Long}, Long},
	[__NR_add_key] = {"add_key", {Ptr, Ptr, Ptr, Long, Long}, Long},
	[__NR_request_key] = {"request_key", {Ptr, Ptr, Ptr, Long}, Long},
	[__NR_keyctl] = {"keyctl", {Long, Long, Long, Long, Long}, Long},
	[__NR_inotify_init] = {"inotify_init", {None}, Long},
	[__NR_inotify_add_watch] = {"inotify_add_watch", {Long, Ptr, Long}, Long},
	[__NR_inotify_rm_watch] = {"inotify_rm_watch", {Long, Long}, Long},
	[__NR_migrate_pages] = {"migrate_pages", {Long, Long, Ptr, Ptr}, Long},
	[__NR_openat] = {"openat", {Long, Ptr, Long}, Long},
	[__NR_mkdirat] = {"mkdirat", {Long, Ptr, Long}, Long},
	[__NR_mknodat] = {"mknodat", {Long, Ptr, Long, Long}, Long},
	[__NR_fchownat] = {"fchownat", {Long, Ptr, Long, Long, Long}, Long},
	[__NR_futimesat] = {"futimesat", {Long, Ptr, Long}, Long},
	[__NR_unlinkat] = {"unlinkat", {Long, Ptr, Long}, Long},
	[__NR_renameat] = {"renameat", {Long, Ptr, Long, Ptr}, Long},
	[__NR_linkat] = {"linkat", {Long, Ptr, Long, Ptr, Long}, Long},
	[__NR_symlinkat] = {"symlinkat", {Ptr, Long, Ptr}, Long},
	[__NR_readlinkat] = {"readlinkat", {Long, Long, Long, Long}, Long},
	[__NR_fchmodat] = {"fchmodat", {Long, Ptr, Long, Long}, Long},
	[__NR_faccessat] = {"faccessat", {Long, Ptr, Long, Long}, Long},
	[__NR_ppoll] = {"ppoll", {Ptr, Long, Ptr, Ptr}, Long},
	[__NR_unshare] = {"unshare", {Long}, Long},
	[__NR_splice] = {"splice", {Long, Ptr, Long, Ptr, Long, Long}, Long},
	[__NR_tee] = {"tee", {Long, Long, Long, Long}, Long},
	[__NR_sync_file_range] = {"sync_file_range", {Long, Long, Long, Long}, Long},
	[__NR_vmsplice] = {"vmsplice", {Long, Ptr, Long, Long}, Long},
	[__NR_move_pages] = {"move_pages", {Long, Long, Ptr, Ptr, Ptr, Long}, Long},
	[__NR_utimensat] = {"utimensat", {Long, Ptr, Long, Long}, Long},
	[__NR_epoll_pwait] = {"epoll_pwait", {Long, Ptr, Long, Long, Ptr}, Long},
	[__NR_signalfd] = {"signalfd", {Long, Ptr, Long}, Long},
	[__NR_timerfd_create] = {"timerfd_create", {Long, Long}, Long},
	[__NR_eventfd] = {"eventfd", {Long, Long}, Long},
	[__NR_fallocate] = {"fallocate", {Long, Long, Long, Long}, Long},
	[__NR_timerfd_settime] = {"timerfd_settime", {Long, Long, Ptr, Ptr}, Long},
	[__NR_timerfd_gettime] = {"timerfd_gettime", {Long, Ptr}, Long},
	[__NR_accept4] = {"accept4", {Long, Long, Long, Long}, Long},
	[__NR_epoll_create1] = {"epoll_create1", {Long}, Long},
	[__NR_dup3] = {"dup3", {Long, Long, Long}, Long},
	[__NR_pipe2] = {"pipe2", {Long, Long}, Long},
	[__NR_inotify_init1] = {"inotify_init1", {Long}, Long},
	[__NR_preadv] = {"preadv", {Long, Ptr, Long, Long}, Long},
	[__NR_pwritev] = {"pwritev", {Long, Ptr, Long, Long}, Long},
	[__NR_perf_event_open] = {"perf_event_open", {Long, Long, Long, Long, Long}, Long},
	[__NR_recvmmsg] = {"recvmmsg", {Long, Ptr, Long, Long, Ptr}, Long},
	[__NR_fanotify_init] = {"fanotify_init", {Long, Long}, Long},
	[__NR_fanotify_mark] = {"fanotify_mark", {Long, Long, Long, Long, Ptr}, Long},
	[__NR_name_to_handle_at] = {"name_to_handle_at", {Long, Ptr, Ptr, Ptr, Long}, Long},
	[__NR_open_by_handle_at] = {"open_by_handle_at", {Long, Ptr, Long}, Long},
	[__NR_clock_adjtime] = {"clock_adjtime", {Long, Ptr}, Long},
	[__NR_syncfs] = {"syncfs", {Long}, Long},
	[__NR_sendmmsg] = {"sendmmsg", {Long, Ptr, Long, Long}, Long},
	[__NR_setns] = {"setns", {Long, Long}, Long},
	[__NR_getcpu] = {"getcpu", {Ptr, Ptr}, Long},
	[__NR_process_vm_readv] = {"process_vm_readv", {Long, Ptr, Long, Ptr, Long, Long}, Long},
	[__NR_process_vm_writev] = {"process_vm_writev", {Long, Ptr, Long, Ptr, Long, Long}, Long},
	[__NR_renameat2] = {"renameat2", {Long, Ptr, Long, Ptr, Long}, Long},
	[__NR_getrandom] = {"getrandom", {Ptr, Long, Long}, Long},
	[__NR_memfd_create] = {"memfd_create", {Ptr, Long}, Long},
	[__NR_bpf] = {"bpf", {Long, Ptr, Long}, Long},
	[__NR_execveat] = {"execveat", {Long, Ptr, Long, Long, Long}, Long},
	[__NR_membarrier] = {"membarrier", {Long, Long}, Long},
	[__NR_mlock2] = {"mlock2", {Ptr, Long, Long}, Long},
	[__NR_copy_file_range] = {"copy_file_range", {Long, Ptr, Long, Ptr, Long, Long}, Long},
	[__NR_preadv2] = {"preadv2", {Long, Ptr, Long, Long, Long}, Long},
	[__NR_pwritev2] = {"pwritev2", {Long, Ptr, Long, Long, Long}, Long},
	[__NR_pkey_mprotect] = {"pkey_mprotect", {Ptr, Long, Long, Long}, Long},
	[__NR_pkey_alloc] = {"pkey_alloc", {Long, Long}, Long},
	[__NR_pkey_free] = {"pkey_free", {Long}, Long},
	[__NR_statx] = {"statx", {Long, Long, Long, Long, Long}, Long},
	[__NR_pidfd_open] = {"pidfd_open", {Long, Long}, Long},
	[__NR_close_range] = {"close_range", {Long, Long, Long}, Long},
	[__NR_epoll_pwait2] = {"epoll_pwait2", {Long, Ptr, Long, Ptr, Ptr}, Long},
};
