#pragma once

enum {
	SYSCALL_NOTHING = 0, // do nothing
	SYSCALL_EXIT, // exit
	SYSCALL_FORK, // fork
	SYSCALL_READ, // read fd
	SYSCALL_WRITE = 4, // write to fd
	SYSCALL_GETPPID, // get parent process id
	SYSCALL_REBOOT, // reboot
	SYSCALL_IPC = 117, // ipc
	SYSCALL_UNAME = 122, // uname
	SYSCALL_VM86 = 166, // enter v86 mode
};
