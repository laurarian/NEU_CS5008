	.file	"main.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Welcome to the Guessing Game!"
.LC1:
	.string	"=========================="
.LC2:
	.string	"CPU Says: Pick a number 1-%d\n"
.LC3:
	.string	"Make a guess:"
.LC4:
	.string	"%d"
.LC5:
	.string	"No guess higher!"
.LC6:
	.string	"No guess lower!"
.LC7:
	.string	"You got it!"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC8:
	.string	"================================================="
	.align 8
.LC9:
	.string	"|Here are the results of your guessing abilities|"
	.section	.rodata.str1.1
.LC10:
	.string	"Game %d took you %d guesses\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB22:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	xorl	%edi, %edi
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	call	time
	leaq	16(%rsp), %rbp
	movl	%eax, %edi
	leaq	20(%rbp), %r12
	call	srand
	movl	$.LC0, %edi
	call	puts
.L6:
	call	rand
	movl	$1717986919, %edx
	movl	$.LC1, %edi
	xorl	%r13d, %r13d
	movl	%eax, %ebx
	imull	%edx
	movl	$0, 12(%rsp)
	movl	%ebx, %eax
	sarl	$31, %eax
	sarl	$2, %edx
	subl	%eax, %edx
	leal	(%rdx,%rdx,4), %eax
	addl	%eax, %eax
	subl	%eax, %ebx
	call	puts
	movl	$10, %esi
	xorl	%eax, %eax
	addl	$1, %ebx
	movl	$.LC2, %edi
	call	printf
	movl	$.LC1, %edi
	call	puts
	cmpl	12(%rsp), %ebx
	jne	.L5
	jmp	.L2
	.p2align 4,,10
	.p2align 3
.L3:
	jg	.L14
.L4:
	cmpl	%edx, %ebx
	je	.L2
.L5:
	movl	$.LC3, %edi
	xorl	%eax, %eax
	addl	$1, %r13d
	call	printf
	leaq	12(%rsp), %rsi
	movl	$.LC4, %edi
	xorl	%eax, %eax
	call	__isoc99_scanf
	movl	12(%rsp), %edx
	cmpl	%ebx, %edx
	jge	.L3
	movl	$.LC5, %edi
	call	puts
	movl	12(%rsp), %edx
	cmpl	%edx, %ebx
	jne	.L5
.L2:
	movl	$.LC7, %edi
	addq	$4, %rbp
	call	puts
	movl	%r13d, -4(%rbp)
	cmpq	%r12, %rbp
	jne	.L6
	movl	$.LC8, %edi
	xorl	%ebx, %ebx
	call	puts
	movl	$.LC9, %edi
	call	puts
	movl	$.LC8, %edi
	call	puts
.L7:
	movl	16(%rsp,%rbx,4), %edx
	movl	%ebx, %esi
	movl	$.LC10, %edi
	xorl	%eax, %eax
	addq	$1, %rbx
	call	printf
	cmpq	$5, %rbx
	jne	.L7
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L14:
	.cfi_restore_state
	movl	$.LC6, %edi
	call	puts
	movl	12(%rsp), %edx
	jmp	.L4
	.cfi_endproc
.LFE22:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.5.0 20210514 (Red Hat 8.5.0-18)"
	.section	.note.GNU-stack,"",@progbits
