	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	_nothing                ## -- Begin function nothing
	.p2align	4, 0x90
_nothing:                               ## @nothing
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	$0, -16(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$1000000, -16(%rbp)     ## imm = 0xF4240
	jae	LBB0_4
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	_mails(%rip), %eax
	addl	$1, %eax
	movl	%eax, _mails(%rip)
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	-16(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -16(%rbp)
	jmp	LBB0_1
LBB0_4:
	xorl	%eax, %eax
                                        ## kill: def $rax killed $eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	xorl	%eax, %eax
	movl	%eax, %ecx
	movl	$0, -4(%rbp)
	leaq	-16(%rbp), %rdi
	movq	%rcx, %rsi
	leaq	_nothing(%rip), %rdx
	callq	_pthread_create
	cmpl	$0, %eax
	je	LBB1_2
## %bb.1:
	movl	$2, %edi
	leaq	L_.str(%rip), %rsi
	movl	$22, %edx
	callq	_write
	movq	%rax, -32(%rbp)         ## 8-byte Spill
LBB1_2:
	xorl	%eax, %eax
	movl	%eax, %ecx
	leaq	-16(%rbp), %rdi
	movq	%rcx, %rsi
	leaq	_nothing(%rip), %rdx
	callq	_pthread_create
	cmpl	$0, %eax
	je	LBB1_4
## %bb.3:
	movl	$2, %edi
	leaq	L_.str(%rip), %rsi
	movl	$22, %edx
	callq	_write
	movq	%rax, -40(%rbp)         ## 8-byte Spill
LBB1_4:
	xorl	%eax, %eax
	movl	%eax, %esi
	movq	-16(%rbp), %rdi
	callq	_pthread_join
	xorl	%ecx, %ecx
	movl	%ecx, %esi
	movq	-24(%rbp), %rdi
	movl	%eax, -44(%rbp)         ## 4-byte Spill
	callq	_pthread_join
	movl	_mails(%rip), %esi
	leaq	L_.str.1(%rip), %rdi
	movl	%eax, -48(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%eax, -52(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_mails                  ## @mails
.zerofill __DATA,__common,_mails,4,2
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Failed to creat thread"

L_.str.1:                               ## @.str.1
	.asciz	"%d"


.subsections_via_symbols
