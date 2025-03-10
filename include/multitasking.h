#pragma once

#include <stdint.h>

typedef struct {
	uint16_t * name;
	uint64_t pid;
	void * stack;
	uintptr_t stack_size;
	uint32_t ebp, esp, eip;
	void * active_process;
	int killed;
	int system;
	int quantum;
	void * fpusave;
	void * windows;
	void * allocations;
	void * allocations_top;
	void * recv_event;
	void * recv_global_event;
	void * stdin_handler;
	void * stdout_handler;
	void * kill;
	void * stdin_priv;
	void * stdin_buffer;
	void * stdin_size;
	void * stdout_priv;
} process_t;
