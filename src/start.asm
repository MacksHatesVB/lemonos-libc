bits 32
align 16

extern __runtime_entry
extern _start
_start:
	; i am angery
	sub esp, 0xf0
	mov ebp, esp
	and ebp, 0xfffffff0
	mov eax, 0
	mov ebx, 0
	mov ecx, 0
	mov edx, 0
	call __runtime_entry
	mov ebx, eax
	mov eax, 1
	int 0x80
.loop:
	hlt
	jmp .loop
