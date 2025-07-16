bits 32

extern prctl
prctl:
	pusha
	mov eax, 172
	mov ebx, [esp + 32 + 4]
	mov ecx, [esp + 32 + 8]
	mov edx, [esp + 32 + 12]
	mov esi, [esp + 32 + 16]
	mov edi, [esp + 32 + 20]
	int 0x80
	mov DWORD [esp + 28], eax
	popa
	ret
