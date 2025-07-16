bits 32

extern __reloc_get_reference_offset
__reloc_get_reference_offset:
	mov eax, reference_symbol	; get reference_symbol file offset
	ret

extern __reloc_get_reference_vaddr
__reloc_get_reference_vaddr:
	call .thunk
.thunk:
	pop eax
	add eax, reference_symbol - .thunk
	ret

extern __reloc_get_base_vaddr
__reloc_get_base_vaddr:
	push ebx
	call .thunk
.thunk:
	pop eax
	add eax, reference_symbol - .thunk
	mov ebx, reference_symbol
	sub eax, ebx
	pop ebx
	ret

reference_symbol:
