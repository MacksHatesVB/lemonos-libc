bits 32

extern fcos
fcos:
	fld DWORD [esp+4]
	fcos
	ret

extern fsin
fsin:
	fld DWORD [esp+4]
	fsin
	ret
