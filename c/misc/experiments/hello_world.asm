section .text
	global _start

section .data
	msg	db	'Hello, world',0xa
	len equ	$ - msg

_start:
	mov	edx,len
	mov ecx,msg
	mov ebx,1
	mov eax,1	
	int 0x80

	mov eax,60
	int 0x80
