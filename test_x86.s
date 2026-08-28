	.att_syntax
	.file	"test_va.c"
	.text
	.globl	builtin_va_list_test            # -- Begin function builtin_va_list_test
	.prefalign	4, .Lfunc_end0, nop
	.type	builtin_va_list_test,@function
builtin_va_list_test:                   # @builtin_va_list_test
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$88, %rsp
	.cfi_def_cfa_offset 96
	movq	%rsi, -88(%rsp)
	leaq	-96(%rsp), %rax
	movq	%rax, -112(%rsp)
	leaq	96(%rsp), %rax
	movq	%rax, -120(%rsp)
	movabsq	$206158430216, %rax             # imm = 0x3000000008
	movq	%rax, -128(%rsp)
	movl	$8, %ecx
	cmpq	$40, %rcx
	ja	.LBB0_2
# %bb.1:                                # %vaarg.in_reg
	movl	$8, %eax
	addq	-112(%rsp), %rax
	addl	$8, %ecx
	movl	%ecx, -128(%rsp)
	movl	(%rax), %eax
	addq	$88, %rsp
	.cfi_def_cfa_offset 8
	retq
.LBB0_2:                                # %vaarg.in_mem
	.cfi_def_cfa_offset 96
	movq	-120(%rsp), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, -120(%rsp)
	movl	(%rax), %eax
	addq	$88, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	builtin_va_list_test, .Lfunc_end0-builtin_va_list_test
	.cfi_endproc
                                        # -- End function
	.ident	"clang version 24.0.0git (https://github.com/AZero13/llvm-project.git 47fbed1a965d889fbb94b9d648ca828ab17d0be7)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
