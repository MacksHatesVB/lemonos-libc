bits 32
align 16

extern hlt ; sleepy for a little processor
hlt:
	hlt
	ret

extern sleep ; sleepy forever
sleep:
	hlt
	jmp sleep

extern disable_irq ; disable interrupts
disable_irq:
	cli
	ret

extern enable_irq ; now enable them
enable_irq:
	sti
	ret

extern save_irq ; save interrupt flag
save_irq:
	pushf
	pop eax
	shr eax, 9
	and eax, 1
	ret

extern restore_irq ; restore interrupt flag
restore_irq:
	mov eax, [esp+4]
	test eax, eax
	jz .no
	sti
	ret
.no:
	cli
	ret

