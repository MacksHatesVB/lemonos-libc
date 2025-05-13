bits 32

; assembly yay

extern syscall
syscall:
	pusha
	mov eax, [esp + 32 + 4]
	mov ebx, [esp + 32 + 8]
	mov ecx, [esp + 32 + 12]
	mov edx, [esp + 32 + 16]
	mov esi, [esp + 32 + 20]
	mov edi, [esp + 32 + 24]
	mov ebp, [esp + 32 + 28]
        int 0x80
	mov DWORD [esp + 28], eax
	popa
	ret
