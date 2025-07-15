bits 32

extern open
open:
	pusha
	mov eax, 5
	mov ebx, [esp + 32 + 4]
	mov ecx, [esp + 32 + 8]
	mov edx, [esp + 32 + 12]
	int 0x80
	mov DWORD [esp + 28], eax
	popa
	ret
