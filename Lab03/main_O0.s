	.file	"main.c"
	.text
	.section	.rodata
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
	.align 8
.LC8:
	.string	"================================================="
	.align 8
.LC9:
	.string	"|Here are the results of your guessing abilities|"
.LC10:
	.string	"Game %d took you %d guesses\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rsp, %rax
	movq	%rax, %rbx
	movl	$5, -64(%rbp)
	movl	$10, -68(%rbp)
	movl	$0, %edi
	call	time
	movl	%eax, %edi
	call	srand
	movl	-64(%rbp), %eax
	cltq
	subq	$1, %rax
	movq	%rax, -80(%rbp)
	movl	-64(%rbp), %eax
	cltq
	movq	%rax, %r14
	movl	$0, %r15d
	movl	-64(%rbp), %eax
	cltq
	movq	%rax, %r12
	movl	$0, %r13d
	movl	-64(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %esi
	movl	$0, %edx
	divq	%rsi
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -88(%rbp)
	movl	$.LC0, %edi
	call	puts
	movl	$0, -60(%rbp)
	jmp	.L2
.L6:
	call	rand
	movl	%eax, %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	leal	1(%rdx), %eax
	movl	%eax, -92(%rbp)
	movl	$0, -96(%rbp)
	movl	$0, -56(%rbp)
	movl	$.LC1, %edi
	call	puts
	movl	-68(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC1, %edi
	call	puts
	jmp	.L3
.L5:
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	leaq	-96(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	addl	$1, -56(%rbp)
	movl	-96(%rbp), %eax
	cmpl	%eax, -92(%rbp)
	jle	.L4
	movl	$.LC5, %edi
	call	puts
	jmp	.L3
.L4:
	movl	-96(%rbp), %eax
	cmpl	%eax, -92(%rbp)
	jge	.L3
	movl	$.LC6, %edi
	call	puts
.L3:
	movl	-96(%rbp), %eax
	cmpl	%eax, -92(%rbp)
	jne	.L5
	movl	$.LC7, %edi
	call	puts
	movq	-88(%rbp), %rax
	movl	-60(%rbp), %edx
	movslq	%edx, %rdx
	movl	-56(%rbp), %ecx
	movl	%ecx, (%rax,%rdx,4)
	addl	$1, -60(%rbp)
.L2:
	movl	-60(%rbp), %eax
	cmpl	-64(%rbp), %eax
	jl	.L6
	movl	$.LC8, %edi
	call	puts
	movl	$.LC9, %edi
	call	puts
	movl	$.LC8, %edi
	call	puts
	movl	$0, -52(%rbp)
	jmp	.L7
.L8:
	movq	-88(%rbp), %rax
	movl	-52(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %edx
	movl	-52(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC10, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -52(%rbp)
.L7:
	movl	-52(%rbp), %eax
	cmpl	-64(%rbp), %eax
	jl	.L8
	movl	$0, %eax
	movq	%rbx, %rsp
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.5.0 20210514 (Red Hat 8.5.0-18)"
	.section	.note.GNU-stack,"",@progbits
