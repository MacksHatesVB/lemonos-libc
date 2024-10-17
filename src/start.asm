bits 32
align 16

extern main
extern _start
_start:
	add esp, 4 ; strange
        pop eax
        pop ecx
        push ecx
        push eax
        call main
        mov ebx, eax
        mov eax, 1
        int 0x80
.loop:
        hlt
        jmp .loop
