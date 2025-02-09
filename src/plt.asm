bits 32

section .plt
.plt:
	push DWORD [ebx+0x4]
	jmp [ebx+0x8]
	nop DWORD [eax+0x0]
	endbr32
	push 0
	jmp .plt
	xchg ax, ax
	endbr32
	push 0x8
	jmp .plt
	xchg ax, ax
	endbr32
	push 0x10
	jmp .plt
	xchg ax, ax
	endbr32
	push 0x18
	jmp .plt
	xchg ax, ax
