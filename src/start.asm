bits 32
align 16

extern __runtime_entry
extern _start
_start:
	pop eax
	push esp
	push eax
	call __runtime_entry
	mov ebx, eax
	mov eax, 1
	int 0x80
.loop:
	hlt
	jmp .loop
