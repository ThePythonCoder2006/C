	.file	"test2.c"
	.text
	.globl	_abs2
	.def	_abs2;	.scl	2;	.type	32;	.endef
_abs2:
LFB14:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	cmpl	$0, -4(%ebp)
	jns	L2
	notl	-8(%ebp)
	notl	-4(%ebp)
	addl	$1, -8(%ebp)
	adcl	$0, -4(%ebp)
L2:
	movl	-8(%ebp), %eax
	movl	-4(%ebp), %edx
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE14:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "error for i = %I64d\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB15:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%esi
	pushl	%ebx
	andl	$-16, %esp
	subl	$48, %esp
	.cfi_offset 6, -12
	.cfi_offset 3, -16
	call	___main
	movl	$-2147483646, 40(%esp)
	movl	$-1, 44(%esp)
	jmp	L5
L7:
	movl	40(%esp), %eax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	movl	%eax, 24(%esp)
	cltd
	movl	%edx, 28(%esp)
	movl	40(%esp), %eax
	movl	44(%esp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_abs2
	movl	24(%esp), %ecx
	xorl	%eax, %ecx
	movl	%ecx, %ebx
	movl	28(%esp), %ecx
	xorl	%edx, %ecx
	movl	%ecx, %esi
	movl	%esi, %eax
	orl	%ebx, %eax
	testl	%eax, %eax
	je	L6
	movl	40(%esp), %eax
	movl	44(%esp), %edx
	movl	%eax, 4(%esp)
	movl	%edx, 8(%esp)
	movl	$LC0, (%esp)
	call	_printf
L6:
	addl	$1, 40(%esp)
	adcl	$0, 44(%esp)
L5:
	cmpl	$0, 44(%esp)
	js	L7
	cmpl	$0, 44(%esp)
	jg	L10
	cmpl	$2147483647, 40(%esp)
	jbe	L7
L10:
	movl	$0, %eax
	leal	-8(%ebp), %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE15:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
