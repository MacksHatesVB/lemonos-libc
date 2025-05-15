#pragma once

enum {
	SYSCALL_NOTHING = 0, // do nothing
	SYSCALL_EXIT, // exit
	SYSCALL_FORK, // fork
	SYSCALL_READ, // read fd
	SYSCALL_WRITE, // write to fd
	SYSCALL_OPEN, // open file
	SYSCALL_CLOSE, // close fd
	SYSCALL_WAITPID, // wait for process to exit
	SYSCALL_CREAT, // create file
	SYSCALL_LINK, // do nothing
	SYSCALL_UNLINK, // do nothing
	SYSCALL_EXECVE, // execute shit
	SYSCALL_CHDIR, // change directory
	SYSCALL_TIME, // get time
	SYSCALL_MKNOD, // do nothing (maybe)
	SYSCALL_CHMOD, // do nothing
	SYSCALL_LCHOWN, // do nothing
	SYSCALL_BREAK, // do nothing
	SYSCALL_OLDSTAT, // do nothing
	SYSCALL_LSEEK = 140, // seek file descriptor
	SYSCALL_GETPID, // get process id
	SYSCALL_MOUNT, // mount (possibly?)
	SYSCALL_UMOUNT, // unmount (possibly?)
	SYSCALL_SETUID, // set process user id
	SYSCALL_GETUID, // get process user id
	SYSCALL_STIME, // do nothing
	SYSCALL_PTRACE, // do nothing
	SYSCALL_ALARM, // trigger SIG_ALARM in n seconds
	SYSCALL_OLDFSTAT, // do nothing
	SYSCALL_PAUSE, // wait for signal
	SYSCALL_UTIME, // do nothing
	SYSCALL_STTY, // do nothing
	SYSCALL_GTTY, // do nothing
	SYSCALL_ACCESS, // do nothing
	SYSCALL_NICE, // do nothing
	SYSCALL_FTIME, // do nothing
	SYSCALL_SYNC, // do nothing
	SYSCALL_KILL, // send signal to process
	SYSCALL_OLDUNAME = 59, // old uname
	SYSCALL_GETPPID, // get parent process id
	SYSCALL_REBOOT, // reboot
	SYSCALL_GETTIMEOFDAY = 78,
	SYSCALL_STAT = 106,
	SYSCALL_SYSINFO = 116,
	SYSCALL_IPC, // ipc
	SYSCALL_UNAME = 122, // ipc
	SYSCALL_SCHED_YIELD = 158,
	SYSCALL_VM86 = 166, // enter v86 mode
	SYSCALL_PRCTL = 172,
	SYSCALL_GETLOCALE = 222,
	SYSCALL_GETTHERM = 223,
	SYSCALL_LCTL = 251,
	SYSCALL_GETRANDOM = 355,
	SYSCALL_SOCKET = 359,
	SYSCALL_SOCKETPAIR,
	SYSCALL_BIND,
	SYSCALL_CONNECT,
	SYSCALL_LISTEN,
	SYSCALL_ACCEPT4,
	SYSCALL_GETSOCKOPT,
	SYSCALL_SETSOCKOPT,
	SYSCALL_GETSOCKNAME,
	SYSCALL_GETPEERNAME,
	SYSCALL_SENDTO,
	SYSCALL_SENDMSG,
	SYSCALL_RECVFROM,
	SYSCALL_SHUTDOWN,
	SYSCALL_MALLOC = 385,
	SYSCALL_FREE = 386,
};

int syscall(const int number, ...);
