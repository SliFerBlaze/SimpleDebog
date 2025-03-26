/*
** EPITECH PROJECT, 2021
** strace
** File description:
** syscalls table
*/

#ifndef SYSCALL_H_
#define SYSCALL_H_

#include <stdlib.h>
#include <string>

#define NUM 1
#define STRING 2
#define UNSIGNED 3
#define VOID_P (4)
#define CONST_VOID_P (5)
#define STRUCT_P (7)
#define STRUCT_STAT_P (8)
#define STRUCT_FD_P (9)
#define PVOID (12)
#define CONST_KERNEL_SIGSET_T_P (13)
#define KERNEL_SIGSET_T_P (14)
#define VARGS (16)
#define CONST_STRUCT_IOVEC_P (17)
#define FD_SET_P (18)
#define STRUCT_TIMEVAL_P (19)
#define VOID (20)
#define STRUCT_SHMID_DS_P (23)
#define CONST_STRUCT_TIMESPEC_P (24)
#define STRUCT_TIMESPEC_P (25)
#define STRUCT_ITIMERVAL_P (26)
#define CONST_STRUCT_ITIMERVAL_P (28)
#define CONST_STRUCT_SOCKADDR_P (31)
#define SOCKLEN_T (32)
#define STRUCT_SOCKADDR_P (33)
#define SOCKLEN_T_P (34)
#define CONST_STRUCT_MSGHDR_P (35)
#define STRUCT_MSGHDR_P (36)
#define STRUCT_RUSAGE_P (39)
#define STRUCT_UTSNAME_P (40)
#define STRUCT_SEMBUF_P (41)
#define STRUCT_MSQID_DS_P (43)
#define STRUCT_LINUX_DIRENT_P (44)
#define MODE_T (49)
#define UID_T (51)
#define GID_T (52)
#define STRUCT_TIMEZONE_P (53)
#define STRUCT_RLIMIT_P (54)
#define CLOCK_T (55)
#define STRUCT_TMS_P (56)
#define ENUM_____REQUEST (57)
#define CONST_GID_T_P (58)
#define UID_T_P (59)
#define GID_T_P (60)
#define CAP_USER_HEADER_T (61)
#define CAP_USER_DATA_T (62)
#define CONST_CAP_USER_DATA_T (63)
#define CONST_STACK_T_P (64)
#define STACK_T_P (65)
#define CONST_STRUCT_UTIMBUF_P (66)
#define DEV_T (67)
#define STRUCT_STATFS_P (68)
#define ID_T (69)
#define CONST_STRUCT_SCHED_PARAM_P (70)
#define STRUCT_SCHED_PARAM_P (71)
#define STRUCT_TIMESPEC_P_ (72)
#define STRUCT____ARGS_P (73)
#define STRUCT_TIMEX_P (74)
#define CONST_STRUCT_RLIMIT_P (75)
#define CONST_STRUCT_TIMEVAL_P (76)
#define CONST_STRUCT_TIMEZONE_P (77)
#define CADDR_T (78)
#define STRUCT_KERNEL_SYM_P (79)
#define NUM_P (80)
#define STRUCT_NFSCTL_ARG_P (81)
#define UNION_NFSCTL_RES_P (82)
#define OFF64_T (83)
#define TIME_T (84)
#define _T___T_P (85)
#define CONST_CPU_SET_T_P (86)
#define CPU_SET_T_P (87)
#define STRUCT_USER_DESC_P (88)
#define AIO_CONTEXT_T_P (90)
#define AIO_CONTEXT_T (91)
#define STRUCT_IO_EVENT_P (92)
#define STRUCT_IOCB_P (93)
#define U64 (94)
#define STRUCT_LINUX_DIRENT64_P (95)
#define CLOCKID_T (96)
#define STRUCT_SIGEVENT_P (97)
#define TIMER_T_P (98)
#define TIMER_T (99)
#define CONST_STRUCT_ITIMERSPEC_P (100)
#define STRUCT_ITIMERSPEC_P (101)
#define STRUCT_EPOLL_EVENT_P (102)
#define CONST_STRUCT_TIMEVAL (103)
#define CONST_UNSIGNED_P (104)
#define UNSIGNED_P (105)
#define MQD_T (106)
#define CONST_STRUCT_SIGEVENT_P (108)
#define STRUCT_MQ_ATTR_P (109)
#define STRUCT_KEXEC_SEGMENT_P (110)
#define IDTYPE_T (111)
#define SIGINFO_T_P (112)
#define KEY_SERIAL_T (113)
#define UNUM32_T (114)
#define STRUCT_POLLFD_P (115)
#define CONST_SIGSET_T_P (116)
#define STRUCT_ROBUST_LIST_HEAD_P (117)
#define LNUM_P (118)
#define CONST_NUM_P (119)
#define CONST_STRUCT_TIMESPEC (120)
#define STRUCT_PERF_EVENT_ATTR_P (121)
#define STRUCT_MMSGHDR_P (122)
#define UNUM64_T (123)
#define STRUCT_FILE_HANDLE_P (124)
#define STRUCT__CACHE_P (126)
#define STRUCT_SCHED_ATTR_P (127)
#define UNION__ATTR_P (128)

typedef struct syscall_s {
    int id;
    std::string name;
    int nb_param;
    int return_value;
    int param1;
    int param2;
    int param3;
    int param4;
    int param5;
    int param6;
} syscall_t;

typedef struct user_regs_struct user_regs_t;

static syscall_t table[330] = {
    {0, "read", 3, NUM, NUM, VOID_P, NUM, 0, 0, 0},
    {1, "write", 3, NUM, NUM, STRING, NUM, 0, 0, 0},
    {2, "open", 2, NUM, STRING, NUM, 0, 0, 0, 0},
    {3, "close", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {4, "stat", 2, NUM, STRING, STRUCT_STAT_P, 0, 0, 0, 0},
    {5, "fstat", 2, NUM, NUM, STRUCT_STAT_P, 0, 0, 0, 0},
    {6, "lstat", 2, NUM, STRING, STRUCT_STAT_P, 0, 0, 0, 0},
    {7, "poll", 3, NUM, STRUCT_FD_P, UNSIGNED, NUM, 0, 0, 0},
    {8, "lseek", 3, NUM, NUM, NUM, NUM, 0, 0, 0},
    {9, "mmap", 6, PVOID, VOID_P, NUM, NUM, NUM, NUM, NUM},
    {10, "mprotect", 3, NUM, VOID_P, NUM, NUM, 0, 0, 0},
    {11, "munmap", 2, NUM, VOID_P, NUM, 0, 0, 0, 0},
    {12, "brk", 1, NUM, VOID_P, 0, 0, 0, 0, 0},
    {13, "rt_sigaction", 6, 0, 0, 0, 0, 0, 0, 0},
    {14, "rt_sigprocmask", 4, NUM, NUM, CONST_KERNEL_SIGSET_T_P,
     KERNEL_SIGSET_T_P, NUM, 0, 0},
    {15, "rt_sigreturn", 6, 0, 0, 0, 0, 0, 0, 0},
    {16, "ioctl", 3, NUM, NUM, UNSIGNED, VARGS, 0, 0, 0},
    {17, "pread64", 6, 0, 0, 0, 0, 0, 0, 0},
    {18, "pwrite64", 6, 0, 0, 0, 0, 0, 0, 0},
    {19, "readv", 3, NUM, NUM, CONST_STRUCT_IOVEC_P, NUM, 0, 0, 0},
    {20, "writev", 3, NUM, NUM, CONST_STRUCT_IOVEC_P, NUM, 0, 0, 0},
    {21, "access", 2, NUM, STRING, NUM, 0, 0, 0, 0},
    {22, "pipe", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {23, "select", 5, NUM, NUM, FD_SET_P, FD_SET_P, FD_SET_P, STRUCT_TIMEVAL_P,
     0},
    {24, "sched_yield", 1, NUM, VOID, 0, 0, 0, 0, 0},
    {25, "mremap", 0, PVOID, 0, 0, 0, 0, 0, 0},
    {26, "msync", 3, NUM, VOID_P, NUM, NUM, 0, 0, 0},
    {27, "mincore", 3, NUM, VOID_P, NUM, STRING, 0, 0, 0},
    {28, "madvise", 3, NUM, VOID_P, NUM, NUM, 0, 0, 0},
    {29, "shmget", 3, NUM, NUM, NUM, NUM, 0, 0, 0},
    {30, "shmat", 3, PVOID, NUM, CONST_VOID_P, NUM, 0, 0, 0},
    {31, "shmctl", 3, NUM, NUM, NUM, STRUCT_SHMID_DS_P, 0, 0, 0},
    {32, "dup", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {33, "dup2", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {34, "pause", 1, NUM, VOID, 0, 0, 0, 0, 0},
    {35, "nanosleep", 2, NUM, CONST_STRUCT_TIMESPEC_P, STRUCT_TIMESPEC_P, 0, 0,
     0, 0},
    {36, "getitimer", 2, NUM, NUM, STRUCT_ITIMERVAL_P, 0, 0, 0, 0},
    {37, "alarm", 1, UNSIGNED, UNSIGNED, 0, 0, 0, 0, 0},
    {38, "setitimer", 3, NUM, NUM, CONST_STRUCT_ITIMERVAL_P,
     STRUCT_ITIMERVAL_P, 0, 0, 0},
    {39, "getpid", 1, NUM, VOID, 0, 0, 0, 0, 0},
    {40, "sendfile", 4, NUM, NUM, NUM, NUM_P, NUM, 0, 0},
    {41, "socket", 3, NUM, NUM, NUM, NUM, 0, 0, 0},
    {42, "connect", 3, NUM, NUM, CONST_STRUCT_SOCKADDR_P, SOCKLEN_T, 0, 0, 0},
    {43, "accept", 3, NUM, NUM, STRUCT_SOCKADDR_P, SOCKLEN_T_P, 0, 0, 0},
    {44, "sendto", 6, NUM, NUM, CONST_VOID_P, NUM, NUM,
     CONST_STRUCT_SOCKADDR_P, SOCKLEN_T},
    {45, "recvfrom", 6, NUM, NUM, VOID_P, NUM, NUM, STRUCT_SOCKADDR_P,
     SOCKLEN_T_P},
    {46, "sendmsg", 3, NUM, NUM, CONST_STRUCT_MSGHDR_P, NUM, 0, 0, 0},
    {47, "recvmsg", 3, NUM, NUM, STRUCT_MSGHDR_P, NUM, 0, 0, 0},
    {48, "shutdown", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {49, "bind", 3, NUM, NUM, CONST_STRUCT_SOCKADDR_P, SOCKLEN_T, 0, 0, 0},
    {50, "listen", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {51, "getsockname", 3, NUM, NUM, STRUCT_SOCKADDR_P, SOCKLEN_T_P, 0, 0, 0},
    {52, "getpeername", 3, NUM, NUM, STRUCT_SOCKADDR_P, SOCKLEN_T_P, 0, 0, 0},
    {53, "socketpair", 4, NUM, NUM, NUM, NUM, NUM, 0, 0},
    {54, "setsockopt", 5, NUM, NUM, NUM, NUM, CONST_VOID_P, SOCKLEN_T, 0},
    {55, "getsockopt", 5, NUM, NUM, NUM, NUM, VOID_P, SOCKLEN_T_P, 0},
    {56, "clone", 0, NUM, 0, 0, 0, 0, 0, 0},
    {57, "fork", 1, NUM, VOID, 0, 0, 0, 0, 0},
    {58, "vfork", 1, NUM, VOID, 0, 0, 0, 0, 0},
    {59, "execve", 3, NUM, STRING, STRING, STRING, 0, 0, 0},
    {60, "exit", 6, 0, 0, 0, 0, 0, 0, 0},
    {61, "wait4", 4, NUM, NUM, NUM_P, NUM, STRUCT_RUSAGE_P, 0, 0},
    {62, "kill", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {63, "uname", 1, NUM, STRUCT_UTSNAME_P, 0, 0, 0, 0, 0},
    {64, "semget", 3, NUM, NUM, NUM, NUM, 0, 0, 0},
    {65, "semop", 3, NUM, NUM, STRUCT_SEMBUF_P, NUM, 0, 0, 0},
    {66, "semctl", 4, NUM, NUM, NUM, NUM, VARGS, 0, 0},
    {67, "shmdt", 1, NUM, CONST_VOID_P, 0, 0, 0, 0, 0},
    {68, "msgget", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {69, "msgsnd", 4, NUM, NUM, CONST_VOID_P, NUM, NUM, 0, 0},
    {70, "msgrcv", 5, NUM, NUM, VOID_P, NUM, NUM, NUM, 0},
    {71, "msgctl", 3, NUM, NUM, NUM, STRUCT_MSQID_DS_P, 0, 0, 0},
    {72, "fcntl", 0, NUM, 0, 0, 0, 0, 0, 0},
    {73, "flock", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {74, "fsync", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {75, "fdatasync", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {76, "truncate", 2, NUM, STRING, NUM, 0, 0, 0, 0},
    {77, "ftruncate", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {78, "getdents", 3, NUM, UNSIGNED, STRUCT_LINUX_DIRENT_P, UNSIGNED, 0, 0,
     0},
    {79, "getcwd", 2, NUM, STRING, UNSIGNED, 0, 0, 0, 0},
    {80, "chdir", 1, NUM, STRING, 0, 0, 0, 0, 0},
    {81, "fchdir", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {82, "rename", 2, NUM, STRING, STRING, 0, 0, 0, 0},
    {83, "mkdir", 2, NUM, STRING, MODE_T, 0, 0, 0, 0},
    {84, "rmdir", 1, NUM, STRING, 0, 0, 0, 0, 0},
    {85, "creat", 2, NUM, STRING, MODE_T, 0, 0, 0, 0},
    {86, "link", 2, NUM, STRING, STRING, 0, 0, 0, 0},
    {87, "unlink", 1, NUM, STRING, 0, 0, 0, 0, 0},
    {88, "symlink", 2, NUM, STRING, STRING, 0, 0, 0, 0},
    {89, "readlink", 3, NUM, STRING, STRING, NUM, 0, 0, 0},
    {90, "chmod", 2, NUM, STRING, MODE_T, 0, 0, 0, 0},
    {91, "fchmod", 2, NUM, NUM, MODE_T, 0, 0, 0, 0},
    {92, "chown", 3, NUM, STRING, UID_T, GID_T, 0, 0, 0},
    {93, "fchown", 3, NUM, NUM, UID_T, GID_T, 0, 0, 0},
    {94, "lchown", 3, NUM, STRING, UID_T, GID_T, 0, 0, 0},
    {95, "umask", 1, MODE_T, MODE_T, 0, 0, 0, 0, 0},
    {96, "gettimeofday", 2, NUM, STRUCT_TIMEVAL_P, STRUCT_TIMEZONE_P, 0, 0, 0,
     0},
    {97, "getrlimit", 2, NUM, NUM, STRUCT_RLIMIT_P, 0, 0, 0, 0},
    {98, "getrusage", 2, NUM, NUM, STRUCT_RUSAGE_P, 0, 0, 0, 0},
    {99, "sysinfo", 1, NUM, STRUCT_P, 0, 0, 0, 0, 0},
    {100, "times", 1, CLOCK_T, STRUCT_TMS_P, 0, 0, 0, 0, 0},
    {101, "ptrace", 4, NUM, ENUM_____REQUEST, NUM, VOID_P, VOID_P, 0, 0},
    {102, "getuid", 1, UID_T, VOID, 0, 0, 0, 0, 0},
    {103, "syslog", 3, NUM, NUM, STRING, NUM, 0, 0, 0},
    {104, "getgid", 1, GID_T, VOID, 0, 0, 0, 0, 0},
    {105, "setuid", 1, NUM, UID_T, 0, 0, 0, 0, 0},
    {106, "setgid", 1, NUM, GID_T, 0, 0, 0, 0, 0},
    {107, "geteuid", 1, UID_T, VOID, 0, 0, 0, 0, 0},
    {108, "getegid", 1, GID_T, VOID, 0, 0, 0, 0, 0},
    {109, "setpgid", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {110, "getppid", 1, NUM, VOID, 0, 0, 0, 0, 0},
    {111, "getpgrp", 0, NUM, 0, 0, 0, 0, 0, 0},
    {112, "setsid", 1, NUM, VOID, 0, 0, 0, 0, 0},
    {113, "setreuid", 2, NUM, UID_T, UID_T, 0, 0, 0, 0},
    {114, "setregid", 2, NUM, GID_T, GID_T, 0, 0, 0, 0},
    {115, "getgroups", 2, NUM, NUM, GID_T, 0, 0, 0, 0},
    {116, "setgroups", 2, NUM, NUM, CONST_GID_T_P, 0, 0, 0, 0},
    {117, "setresuid", 3, NUM, UID_T, UID_T, UID_T, 0, 0, 0},
    {118, "getresuid", 3, NUM, UID_T_P, UID_T_P, UID_T_P, 0, 0, 0},
    {119, "setresgid", 3, NUM, GID_T, GID_T, GID_T, 0, 0, 0},
    {120, "getresgid", 3, NUM, GID_T_P, GID_T_P, GID_T_P, 0, 0, 0},
    {121, "getpgid", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {122, "setfsuid", 1, NUM, UID_T, 0, 0, 0, 0, 0},
    {123, "setfsgid", 1, NUM, UID_T, 0, 0, 0, 0, 0},
    {124, "getsid", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {125, "capget", 2, NUM, CAP_USER_HEADER_T, CAP_USER_DATA_T, 0, 0, 0, 0},
    {126, "capset", 2, NUM, CAP_USER_HEADER_T, CONST_CAP_USER_DATA_T, 0, 0, 0,
     0},
    {127, "rt_sigpending", 6, 0, 0, 0, 0, 0, 0, 0},
    {128, "rt_sigtimedwait", 6, 0, 0, 0, 0, 0, 0, 0},
    {129, "rt_sigqueueinfo", 6, 0, 0, 0, 0, 0, 0, 0},
    {130, "rt_sigsuspend", 6, 0, 0, 0, 0, 0, 0, 0},
    {131, "sigaltstack", 2, NUM, CONST_STACK_T_P, STACK_T_P, 0, 0, 0, 0},
    {132, "utime", 2, NUM, STRING, CONST_STRUCT_UTIMBUF_P, 0, 0, 0, 0},
    {133, "mknod", 3, NUM, STRING, MODE_T, DEV_T, 0, 0, 0},
    {134, "uselib", 1, NUM, STRING, 0, 0, 0, 0, 0},
    {135, "personality", 1, NUM, UNSIGNED, 0, 0, 0, 0, 0},
    {136, "ustat", 2, NUM, DEV_T, STRUCT_P, 0, 0, 0, 0},
    {137, "statfs", 2, NUM, STRING, STRUCT_P, 0, 0, 0, 0},
    {138, "fstatfs", 2, NUM, NUM, STRUCT_STATFS_P, 0, 0, 0, 0},
    {139, "sysfs", 2, NUM, NUM, STRING, 0, 0, 0, 0},
    {140, "getpriority", 2, NUM, NUM, ID_T, 0, 0, 0, 0},
    {141, "setpriority", 3, NUM, NUM, ID_T, NUM, 0, 0, 0},
    {142, "sched_setparam", 2, NUM, NUM, CONST_STRUCT_SCHED_PARAM_P, 0, 0, 0,
     0},
    {143, "sched_getparam", 2, NUM, NUM, STRUCT_SCHED_PARAM_P, 0, 0, 0, 0},
    {144, "sched_setscheduler", 3, NUM, NUM, NUM, CONST_STRUCT_SCHED_PARAM_P,
     0, 0, 0},
    {145, "sched_getscheduler", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {146, "sched_get_priority_max", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {147, "sched_get_priority_min", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {148, "sched_rr_get_interval", 2, NUM, NUM, STRUCT_TIMESPEC_P_, 0, 0, 0,
     0},
    {149, "mlock", 2, NUM, CONST_VOID_P, NUM, 0, 0, 0, 0},
    {150, "munlock", 2, NUM, CONST_VOID_P, NUM, 0, 0, 0, 0},
    {151, "mlockall", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {152, "munlockall", 1, NUM, VOID, 0, 0, 0, 0, 0},
    {153, "vhangup", 1, NUM, VOID, 0, 0, 0, 0, 0},
    {154, "modify_ldt", 3, NUM, NUM, VOID_P, UNSIGNED, 0, 0, 0},
    {155, "pivot_root", 2, NUM, STRING, STRING, 0, 0, 0, 0},
    {156, "_sysctl", 1, NUM, STRUCT____ARGS_P, 0, 0, 0, 0, 0},
    {157, "prctl", 5, NUM, NUM, UNSIGNED, UNSIGNED, UNSIGNED, UNSIGNED, 0},
    {158, "arch_prctl", 2, NUM, NUM, UNSIGNED, 0, 0, 0, 0},
    {159, "adjtimex", 1, NUM, STRUCT_TIMEX_P, 0, 0, 0, 0, 0},
    {160, "setrlimit", 2, NUM, NUM, CONST_STRUCT_RLIMIT_P, 0, 0, 0, 0},
    {161, "chroot", 1, NUM, STRING, 0, 0, 0, 0, 0},
    {162, "sync", 1, VOID, VOID, 0, 0, 0, 0, 0},
    {163, "acct", 1, NUM, STRING, 0, 0, 0, 0, 0},
    {164, "settimeofday", 2, NUM, CONST_STRUCT_TIMEVAL_P,
     CONST_STRUCT_TIMEZONE_P, 0, 0, 0, 0},
    {165, "mount", 5, NUM, STRING, STRING, STRING, UNSIGNED, CONST_VOID_P, 0},
    {166, "umount2", 2, NUM, STRING, NUM, 0, 0, 0, 0},
    {167, "swapon", 2, NUM, STRING, NUM, 0, 0, 0, 0},
    {168, "swapoff", 1, NUM, STRING, 0, 0, 0, 0, 0},
    {169, "reboot", 4, NUM, NUM, NUM, NUM, VOID_P, 0, 0},
    {170, "sethostname", 2, NUM, STRING, NUM, 0, 0, 0, 0},
    {171, "setdomainname", 2, NUM, STRING, NUM, 0, 0, 0, 0},
    {172, "iopl", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {173, "ioperm", 3, NUM, UNSIGNED, UNSIGNED, NUM, 0, 0, 0},
    {174, "create_module", 2, CADDR_T, STRING, NUM, 0, 0, 0, 0},
    {175, "init_module", 3, NUM, VOID_P, UNSIGNED, STRING, 0, 0, 0},
    {176, "delete_module", 2, NUM, STRING, NUM, 0, 0, 0, 0},
    {177, "get_kernel_syms", 1, NUM, STRUCT_KERNEL_SYM_P, 0, 0, 0, 0, 0},
    {178, "query_module", 5, NUM, STRING, NUM, VOID_P, NUM, NUM_P, 0},
    {179, "quotactl", 4, NUM, NUM, STRING, NUM, CADDR_T, 0, 0},
    {180, "nfsservctl", 3, NUM, NUM, STRUCT_NFSCTL_ARG_P, UNION_NFSCTL_RES_P,
     0, 0, 0},
    {181, "getpmsg", 6, 0, 0, 0, 0, 0, 0, 0},
    {182, "putpmsg", 6, 0, 0, 0, 0, 0, 0, 0},
    {183, "afs_syscall", 6, 0, 0, 0, 0, 0, 0, 0},
    {184, "tuxcall", 6, 0, 0, 0, 0, 0, 0, 0},
    {185, "security", 6, 0, 0, 0, 0, 0, 0, 0},
    {186, "gettid", 1, NUM, VOID, 0, 0, 0, 0, 0},
    {187, "readahead", 3, NUM, NUM, OFF64_T, NUM, 0, 0, 0},
    {188, "setxattr", 5, NUM, STRING, STRING, CONST_VOID_P, NUM, NUM, 0},
    {189, "lsetxattr", 5, NUM, STRING, STRING, CONST_VOID_P, NUM, NUM, 0},
    {190, "fsetxattr", 5, NUM, NUM, STRING, CONST_VOID_P, NUM, NUM, 0},
    {191, "getxattr", 4, NUM, STRING, STRING, VOID_P, NUM, 0, 0},
    {192, "lgetxattr", 4, NUM, STRING, STRING, VOID_P, NUM, 0, 0},
    {193, "fgetxattr", 4, NUM, NUM, STRING, VOID_P, NUM, 0, 0},
    {194, "listxattr", 3, NUM, STRING, STRING, NUM, 0, 0, 0},
    {195, "llistxattr", 3, NUM, STRING, STRING, NUM, 0, 0, 0},
    {196, "flistxattr", 3, NUM, NUM, STRING, NUM, 0, 0, 0},
    {197, "removexattr", 2, NUM, STRING, STRING, 0, 0, 0, 0},
    {198, "lremovexattr", 2, NUM, STRING, STRING, 0, 0, 0, 0},
    {199, "fremovexattr", 2, NUM, NUM, STRING, 0, 0, 0, 0},
    {200, "tkill", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {201, "time", 1, TIME_T, _T___T_P, 0, 0, 0, 0, 0},
    {202, "futex", 0, NUM, 0, 0, 0, 0, 0, 0},
    {203, "sched_setaffinity", 3, NUM, NUM, NUM, CONST_CPU_SET_T_P, 0, 0, 0},
    {204, "sched_getaffinity", 3, NUM, NUM, NUM, CPU_SET_T_P, 0, 0, 0},
    {205, "set_thread_area", 1, NUM, STRUCT_USER_DESC_P, 0, 0, 0, 0, 0},
    {206, "io_setup", 2, NUM, UNSIGNED, AIO_CONTEXT_T_P, 0, 0, 0, 0},
    {207, "io_destroy", 1, NUM, AIO_CONTEXT_T, 0, 0, 0, 0, 0},
    {208, "io_getevents", 5, NUM, AIO_CONTEXT_T, NUM, NUM, STRUCT_IO_EVENT_P,
     STRUCT_TIMESPEC_P, 0},
    {209, "io_submit", 3, NUM, AIO_CONTEXT_T, NUM, STRUCT_IOCB_P, 0, 0, 0},
    {210, "io_cancel", 3, NUM, AIO_CONTEXT_T, STRUCT_IOCB_P, STRUCT_IO_EVENT_P,
     0, 0, 0},
    {211, "get_thread_area", 1, NUM, STRUCT_USER_DESC_P, 0, 0, 0, 0, 0},
    {212, "lookup_dcookie", 3, NUM, U64, STRING, NUM, 0, 0, 0},
    {213, "epoll_create", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {214, "epoll_ctl_old", 6, 0, 0, 0, 0, 0, 0, 0},
    {215, "epoll_wait_old", 6, 0, 0, 0, 0, 0, 0, 0},
    {216, "remap_file_pages", 5, NUM, VOID_P, NUM, NUM, NUM, NUM, 0},
    {217, "getdents64", 3, NUM, UNSIGNED, STRUCT_LINUX_DIRENT64_P, UNSIGNED, 0,
     0, 0},
    {218, "set_tid_address", 1, NUM, NUM_P, 0, 0, 0, 0, 0},
    {219, "restart_syscall", 1, NUM, VOID, 0, 0, 0, 0, 0},
    {220, "semtimedop", 4, NUM, NUM, STRUCT_SEMBUF_P, NUM,
     CONST_STRUCT_TIMESPEC_P, 0, 0},
    {221, "fadvise64", 6, 0, 0, 0, 0, 0, 0, 0},
    {222, "timer_create", 3, NUM, CLOCKID_T, STRUCT_SIGEVENT_P, TIMER_T_P, 0,
     0, 0},
    {223, "timer_settime", 4, NUM, TIMER_T, NUM, CONST_STRUCT_ITIMERSPEC_P,
     STRUCT_ITIMERSPEC_P, 0, 0},
    {224, "timer_gettime", 2, NUM, TIMER_T, STRUCT_ITIMERSPEC_P, 0, 0, 0, 0},
    {225, "timer_getoverrun", 1, NUM, TIMER_T, 0, 0, 0, 0, 0},
    {226, "timer_delete", 1, NUM, TIMER_T, 0, 0, 0, 0, 0},
    {227, "clock_settime", 2, NUM, CLOCKID_T, CONST_STRUCT_TIMESPEC_P, 0, 0, 0,
     0},
    {228, "clock_gettime", 2, NUM, CLOCKID_T, STRUCT_TIMESPEC_P, 0, 0, 0, 0},
    {229, "clock_getres", 2, NUM, CLOCKID_T, STRUCT_TIMESPEC_P, 0, 0, 0, 0},
    {230, "clock_nanosleep", 4, NUM, CLOCKID_T, NUM, CONST_STRUCT_TIMESPEC_P,
     STRUCT_TIMESPEC_P, 0, 0},
    {231, "exit_group", 1, VOID, NUM, 0, 0, 0, 0, 0},
    {232, "epoll_wait", 4, NUM, NUM, STRUCT_EPOLL_EVENT_P, NUM, NUM, 0, 0},
    {233, "epoll_ctl", 4, NUM, NUM, NUM, NUM, STRUCT_EPOLL_EVENT_P, 0, 0},
    {234, "tgkill", 3, NUM, NUM, NUM, NUM, 0, 0, 0},
    {235, "utimes", 2, NUM, STRING, CONST_STRUCT_TIMEVAL, 0, 0, 0, 0},
    {236, "vserver", 6, 0, 0, 0, 0, 0, 0, 0},
    {237, "mbind", 6, NUM, VOID_P, UNSIGNED, NUM, CONST_UNSIGNED_P, UNSIGNED,
     UNSIGNED},
    {238, "set_mempolicy", 3, NUM, NUM, CONST_UNSIGNED_P, UNSIGNED, 0, 0, 0},
    {239, "get_mempolicy", 5, NUM, NUM_P, UNSIGNED_P, UNSIGNED, VOID_P,
     UNSIGNED, 0},
    {240, "mq_open", 2, MQD_T, STRING, NUM, 0, 0, 0, 0},
    {241, "mq_unlink", 1, NUM, STRING, 0, 0, 0, 0, 0},
    {242, "mq_timedsend", 5, NUM, MQD_T, STRING, NUM, UNSIGNED,
     CONST_STRUCT_TIMESPEC_P, 0},
    {243, "mq_timedreceive", 5, NUM, MQD_T, STRING, NUM, UNSIGNED_P,
     CONST_STRUCT_TIMESPEC_P, 0},
    {244, "mq_notify", 2, NUM, MQD_T, CONST_STRUCT_SIGEVENT_P, 0, 0, 0, 0},
    {245, "mq_getsetattr", 3, NUM, MQD_T, STRUCT_MQ_ATTR_P, STRUCT_MQ_ATTR_P,
     0, 0, 0},
    {246, "kexec_load", 4, NUM, UNSIGNED, UNSIGNED, STRUCT_KEXEC_SEGMENT_P,
     UNSIGNED, 0, 0},
    {247, "waitid", 4, NUM, IDTYPE_T, ID_T, SIGINFO_T_P, NUM, 0, 0},
    {248, "add_key", 5, KEY_SERIAL_T, STRING, STRING, CONST_VOID_P, NUM,
     KEY_SERIAL_T, 0},
    {249, "request_key", 4, KEY_SERIAL_T, STRING, STRING, STRING, KEY_SERIAL_T,
     0, 0},
    {250, "keyctl", 2, NUM, NUM, VARGS, 0, 0, 0, 0},
    {251, "ioprio_set", 3, NUM, NUM, NUM, NUM, 0, 0, 0},
    {252, "ioprio_get", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {253, "inotify_init", 1, NUM, VOID, 0, 0, 0, 0, 0},
    {254, "inotify_add_watch", 3, NUM, NUM, STRING, UNUM32_T, 0, 0, 0},
    {255, "inotify_rm_watch", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {256, "migrate_pages", 4, NUM, NUM, UNSIGNED, CONST_UNSIGNED_P,
     CONST_UNSIGNED_P, 0, 0},
    {257, "openat", 3, NUM, NUM, STRING, NUM, 0, 0, 0},
    {258, "mkdirat", 3, NUM, NUM, STRING, MODE_T, 0, 0, 0},
    {259, "mknodat", 4, NUM, NUM, STRING, MODE_T, DEV_T, 0, 0},
    {260, "fchownat", 5, NUM, NUM, STRING, UID_T, GID_T, NUM, 0},
    {261, "futimesat", 3, NUM, NUM, STRING, CONST_STRUCT_TIMEVAL, 0, 0, 0},
    {262, "newfstatat", 6, 0, 0, 0, 0, 0, 0, 0},
    {263, "unlinkat", 3, NUM, NUM, STRING, NUM, 0, 0, 0},
    {264, "renameat", 4, NUM, NUM, STRING, NUM, STRING, 0, 0},
    {265, "linkat", 5, NUM, NUM, STRING, NUM, STRING, NUM, 0},
    {266, "symlinkat", 3, NUM, STRING, NUM, STRING, 0, 0, 0},
    {267, "readlinkat", 4, NUM, NUM, STRING, STRING, NUM, 0, 0},
    {268, "fchmodat", 4, NUM, NUM, STRING, MODE_T, NUM, 0, 0},
    {269, "faccessat", 4, NUM, NUM, STRING, NUM, NUM, 0, 0},
    {270, "pselect6", 6, 0, 0, 0, 0, 0, 0, 0},
    {271, "ppoll", 4, NUM, STRUCT_POLLFD_P, UNSIGNED, CONST_STRUCT_TIMESPEC_P,
     CONST_SIGSET_T_P, 0, 0},
    {272, "unshare", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {273, "set_robust_list", 2, NUM, STRUCT_ROBUST_LIST_HEAD_P, NUM, 0, 0, 0,
     0},
    {274, "get_robust_list", 3, NUM, NUM, STRUCT_ROBUST_LIST_HEAD_P, NUM_P, 0,
     0, 0},
    {275, "splice", 6, NUM, NUM, LNUM_P, NUM, LNUM_P, NUM, UNSIGNED},
    {276, "tee", 4, NUM, NUM, NUM, NUM, UNSIGNED, 0, 0},
    {277, "sync_file_range", 4, NUM, NUM, OFF64_T, OFF64_T, UNSIGNED, 0, 0},
    {278, "vmsplice", 4, NUM, NUM, CONST_STRUCT_IOVEC_P, UNSIGNED, UNSIGNED, 0,
     0},
    {279, "move_pages", 6, NUM, NUM, UNSIGNED, VOID_P, CONST_NUM_P, NUM_P,
     NUM},
    {280, "utimensat", 4, NUM, NUM, STRING, CONST_STRUCT_TIMESPEC, NUM, 0, 0},
    {281, "epoll_pwait", 5, NUM, NUM, STRUCT_EPOLL_EVENT_P, NUM, NUM,
     CONST_SIGSET_T_P, 0},
    {282, "signalfd", 3, NUM, NUM, CONST_SIGSET_T_P, NUM, 0, 0, 0},
    {283, "timerfd_create", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {284, "eventfd", 2, NUM, UNSIGNED, NUM, 0, 0, 0, 0},
    {285, "fallocate", 4, NUM, NUM, NUM, NUM, NUM, 0, 0},
    {286, "timerfd_settime", 4, NUM, NUM, NUM, CONST_STRUCT_ITIMERSPEC_P,
     STRUCT_ITIMERSPEC_P, 0, 0},
    {287, "timerfd_gettime", 2, NUM, NUM, STRUCT_ITIMERSPEC_P, 0, 0, 0, 0},
    {288, "accept4", 4, NUM, NUM, STRUCT_SOCKADDR_P, SOCKLEN_T_P, NUM, 0, 0},
    {289, "signalfd4", 6, 0, 0, 0, 0, 0, 0, 0},
    {290, "eventfd2", 6, 0, 0, 0, 0, 0, 0, 0},
    {291, "epoll_create1", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {292, "dup3", 3, NUM, NUM, NUM, NUM, 0, 0, 0},
    {293, "pipe2", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {294, "inotify_init1", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {295, "preadv", 4, NUM, NUM, CONST_STRUCT_IOVEC_P, NUM, NUM, 0, 0},
    {296, "pwritev", 4, NUM, NUM, CONST_STRUCT_IOVEC_P, NUM, NUM, 0, 0},
    {297, "rt_tgsigqueueinfo", 6, 0, 0, 0, 0, 0, 0, 0},
    {298, "perf_event_open", 5, NUM, STRUCT_PERF_EVENT_ATTR_P, NUM, NUM, NUM,
     UNSIGNED, 0},
    {299, "recvmmsg", 5, NUM, NUM, STRUCT_MMSGHDR_P, UNSIGNED, UNSIGNED,
     STRUCT_TIMESPEC_P, 0},
    {300, "fanotify_init", 2, NUM, UNSIGNED, UNSIGNED, 0, 0, 0, 0},
    {301, "fanotify_mark", 5, NUM, NUM, UNSIGNED, UNUM64_T, NUM, STRING, 0},
    {302, "prlimit64", 6, 0, 0, 0, 0, 0, 0, 0},
    {303, "name_to_handle_at", 5, NUM, NUM, STRING, STRUCT_FILE_HANDLE_P,
     NUM_P, NUM, 0},
    {304, "open_by_handle_at", 3, NUM, NUM, STRUCT_FILE_HANDLE_P, NUM, 0, 0,
     0},
    {305, "clock_adjtime", 6, 0, 0, 0, 0, 0, 0, 0},
    {306, "syncfs", 1, NUM, NUM, 0, 0, 0, 0, 0},
    {307, "sendmmsg", 4, NUM, NUM, STRUCT_MMSGHDR_P, UNSIGNED, UNSIGNED, 0, 0},
    {308, "setns", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {309, "getcpu", 3, NUM, UNSIGNED_P, UNSIGNED_P, STRUCT__CACHE_P, 0, 0, 0},
    {310, "process_vm_readv", 6, NUM, NUM, CONST_STRUCT_IOVEC_P, UNSIGNED,
     CONST_STRUCT_IOVEC_P, UNSIGNED, UNSIGNED},
    {311, "process_vm_writev", 6, NUM, NUM, CONST_STRUCT_IOVEC_P, UNSIGNED,
     CONST_STRUCT_IOVEC_P, UNSIGNED, UNSIGNED},
    {312, "kcmp", 5, NUM, NUM, NUM, NUM, UNSIGNED, UNSIGNED, 0},
    {313, "finit_module", 3, NUM, NUM, STRING, NUM, 0, 0, 0},
    {314, "sched_setattr", 3, NUM, NUM, STRUCT_SCHED_ATTR_P, UNSIGNED, 0, 0,
     0},
    {315, "sched_getattr", 4, NUM, NUM, STRUCT_SCHED_ATTR_P, UNSIGNED,
     UNSIGNED, 0, 0},
    {316, "renameat2", 5, NUM, NUM, STRING, NUM, STRING, UNSIGNED, 0},
    {317, "seccomp", 3, NUM, UNSIGNED, UNSIGNED, VOID_P, 0, 0, 0},
    {318, "getrandom", 3, NUM, VOID_P, NUM, UNSIGNED, 0, 0, 0},
    {319, "memfd_create", 2, NUM, STRING, UNSIGNED, 0, 0, 0, 0},
    {320, "kexec_file_load", 5, NUM, NUM, NUM, UNSIGNED, STRING, UNSIGNED, 0},
    {321, "bpf", 3, NUM, NUM, UNION__ATTR_P, UNSIGNED, 0, 0, 0},
    {322, "execveat", 5, NUM, NUM, STRING, STRING, STRING, NUM, 0},
    {323, "userfaultfd", 6, 0, 0, 0, 0, 0, 0, 0},
    {324, "membarrier", 2, NUM, NUM, NUM, 0, 0, 0, 0},
    {325, "mlock2", 3, NUM, CONST_VOID_P, NUM, NUM, 0, 0, 0},
    {326, "copy_file_range", 6, NUM, NUM, LNUM_P, NUM, LNUM_P, NUM, UNSIGNED},
    {327, "preadv2", 5, NUM, NUM, CONST_STRUCT_IOVEC_P, NUM, NUM, NUM, 0},
    {328, "pwritev2", 5, NUM, NUM, CONST_STRUCT_IOVEC_P, NUM, NUM, NUM, 0},
    {-1, "", 0, 0, 0, 0, 0, 0, 0, 0}};

#endif /* !SYSCALL_H_ */
