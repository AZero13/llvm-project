	.file	"test_va.c"
	.text
	.globl	builtin_va_list_test            // -- Begin function builtin_va_list_test
	.p2align	2
	.type	builtin_va_list_test,@function
builtin_va_list_test:                   // @builtin_va_list_test
	.cfi_startproc
// %bb.0:                               // %entry
	sub	sp, sp, #224
	.cfi_def_cfa_offset 224
	.cfi_remember_state
	mov	x8, #-56                        // =0xffffffffffffffc8
	mov	x9, sp
	add	x10, sp, #136
	movk	x8, #65408, lsl #32
	add	x9, x9, #128
	stp	x1, x2, [sp, #136]
	stp	x9, x8, [sp, #208]
	add	x9, x10, #56
	add	x10, sp, #224
	mov	x8, #-56                        // =0xffffffffffffffc8
	stp	x3, x4, [sp, #152]
	stp	x5, x6, [sp, #168]
	stp	q0, q1, [sp]
	stp	q2, q3, [sp, #32]
	stp	q4, q5, [sp, #64]
	stp	q6, q7, [sp, #96]
	str	x9, [sp, #200]
	stp	x7, x10, [sp, #184]
	tbz	w8, #31, .LBB0_3
// %bb.1:                               // %vaarg.maybe_reg
	add	w9, w8, #8
	cmn	w8, #8
	str	w9, [sp, #216]
	b.hi	.LBB0_3
// %bb.2:                               // %vaarg.in_reg
	ldr	x9, [sp, #200]
	add	x8, x9, x8
	ldr	w0, [x8]
	add	sp, sp, #224
	.cfi_def_cfa_offset 0
	ret
.LBB0_3:                                // %vaarg.on_stack
	.cfi_restore_state
	ldr	x8, [sp, #192]
	add	x9, x8, #8
	str	x9, [sp, #192]
	ldr	w0, [x8]
	add	sp, sp, #224
	.cfi_def_cfa_offset 0
	ret
.Lfunc_end0:
	.size	builtin_va_list_test, .Lfunc_end0-builtin_va_list_test
	.cfi_endproc
                                        // -- End function
	.ident	"clang version 24.0.0git (https://github.com/AZero13/llvm-project.git 47fbed1a965d889fbb94b9d648ca828ab17d0be7)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
