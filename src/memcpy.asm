bits 32

extern asm_memcpy
extern memcpy_aligned_sse2
extern memcpy_aligned_avx
extern memcpy_slow
extern memcpy32

asm_memcpy:
	push esi
	push edi
	push ebx

	mov esi, [esp+16]
	mov edi, [esp+20]
	mov ebx, [esp+24]

; figure out which shitty algorithm we want to use
	mov eax, ebx
	and eax, 0b1111111
	jnz .option2
	call _memcpy_aligned_avx
	jmp .end
.option2:
	mov eax, ebx
	and eax, 0b111111
	jnz .option3
	call _memcpy_aligned_sse2
	jmp .end
.option3:
	call memcpy_slow
.end:

	pop ebx
	pop edi
	pop esi
	ret

memcpy_slow:
.loop:
	mov ah, [esi]
	mov [edi], ah

	add esi, 1
	add edi, 1
	dec ebx
	jnz .loop

	ret

_memcpy_aligned_sse2:
	mov eax, ebx
	and eax, 0b1111111
	shr ebx, 7

.loop:
	movdqa xmm0, [esi]
	movdqa xmm1, [esi+16]
	movdqa xmm2, [esi+32]
	movdqa xmm3, [esi+48]
	movdqa xmm4, [esi+64]
	movdqa xmm5, [esi+80]
	movdqa xmm6, [esi+96]
	movdqa xmm7, [esi+112]

	movdqa [edi], xmm0
	movdqa [edi+16], xmm1
	movdqa [edi+32], xmm2
	movdqa [edi+48], xmm3
	movdqa [edi+64], xmm4
	movdqa [edi+80], xmm5
	movdqa [edi+96], xmm6
	movdqa [edi+112], xmm7

	add esi, 128
	add edi, 128
	dec ebx

	jnz .loop
.end:
;	push esi
;	push edi
;	push eax
;	call memcpy32
;	add esp, 12

	ret


_2memcpy_aligned_sse2:
	mov eax, ebx
	and eax, 0b1111
	shr ebx, 4

.loop:
	prefetchnta [esi+16]
	prefetchnta [esi+32]
	movdqa xmm0, [esi]
	movdqa [edi], xmm0

	add esi, 16
	add edi, 16
	dec ebx

	jnz .loop
.end:
	ret



_memcpy_aligned_avx:
	mov eax, ebx
	and eax, 0b11111111
	shr ebx, 8

.loop:
	vmovdqa ymm0, [esi]
	vmovdqa ymm1, [esi+32]
	vmovdqa ymm2, [esi+64]
	vmovdqa ymm3, [esi+96]
	vmovdqa ymm4, [esi+128]
	vmovdqa ymm5, [esi+160]
	vmovdqa ymm6, [esi+192]
	vmovdqa ymm7, [esi+224]

	vmovdqa [edi], ymm0
	vmovdqa [edi+32], ymm1
	vmovdqa [edi+64], ymm2
	vmovdqa [edi+96], ymm3
	vmovdqa [edi+128], ymm4
	vmovdqa [edi+160], ymm5
	vmovdqa [edi+192], ymm6
	vmovdqa [edi+224], ymm7

	add esi, 256
	add edi, 256
	dec ebx

	jnz .loop
.end:
	ret


_2memcpy_aligned_avx:
	mov eax, ebx
	and eax, 0b11111
	shr ebx, 5

.loop:
	prefetchnta [esi+32]
	prefetchnta [esi+64]
	vmovdqa ymm0, [esi]
	vmovdqa [edi], ymm0
	add esi, 32
	add edi, 32
	dec ebx

	jnz .loop
.end:
	ret


memcpy_aligned_sse2:
	push esi
	push edi
	push ebx

	mov esi, [esp+16]
	mov edi, [esp+20]
	mov ebx, [esp+24]
	call _memcpy_aligned_sse2

	pop ebx
	pop edi
	pop esi
	ret

memcpy_aligned_avx:
	push esi
	push edi
	push ebx

	mov esi, [esp+16]
	mov edi, [esp+20]
	mov ebx, [esp+24]
	call _memcpy_aligned_avx

	pop ebx
	pop edi
	pop esi
	ret

