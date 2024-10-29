#pragma once

#include <stdint.h>
#include <sys/syscall.h>

// this is NOT the real definition of syscall() but it should be fine
void ipc(uint64_t pid, int cmd, void * data);
int reboot(int op);

enum {
	REBOOT_CMD_POWER_OFF,
	REBOOT_CMD_RESTART,
	REBOOT_CMD_SUSPEND,
};
