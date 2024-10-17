#pragma once

// this is NOT the real definition of syscall() but it should be fine
void ipc(uint64_t pid, int cmd, void * data);
int syscall(int number, ...);
