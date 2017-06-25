	.file	"fork-01.c"
	.section	.rodata
	.align 8
.LC0:
	.string	"This line is from pid %d, value = %d\n"
	.text
.globl main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$120, %rsp
	.cfi_offset 3, -24
	call	fork
	movl	$0, %eax
	call	getpid
	movl	%eax, -24(%rbp)
	movl	$1, -20(%rbp)
	jmp	.L2
.L3:
	movl	$.LC0, %ebx
	movl	-20(%rbp), %ecx
	movl	-24(%rbp), %edx
	leaq	-128(%rbp), %rax
	movq	%rbx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movq	%rax, %rdx
	leaq	-128(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	write
	addl	$1, -20(%rbp)
.L2:
	cmpl	$200, -20(%rbp)
	jle	.L3
	addq	$120, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 4.4.5-8) 4.4.5"
	.section	.note.GNU-stack,"",@progbits
