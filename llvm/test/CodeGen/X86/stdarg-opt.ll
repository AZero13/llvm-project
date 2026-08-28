; RUN: opt -mtriple=x86_64-unknown-linux-gnu -passes=optimize-stdarg -S < %s | FileCheck %s

%struct.__va_list_tag = type { i32, i32, ptr, ptr }

; In this test, va_arg is never used.
; CHECK: define double @test_no_va_args(ptr %fmt, ...) #[[ATTR1:[0-9]+]]
define double @test_no_va_args(ptr %fmt, ...) {
entry:
  %a = alloca [1 x %struct.__va_list_tag], align 16
  call void @llvm.va_start(ptr %a)
  call void @llvm.va_end(ptr %a)
  ret double 0.0
}

; In this test, only GPR offset (0) is read
; CHECK: define i32 @test_only_gpr(ptr %fmt, ...) #[[ATTR2:[0-9]+]]
define i32 @test_only_gpr(ptr %fmt, ...) {
entry:
  %a = alloca [1 x %struct.__va_list_tag], align 16
  call void @llvm.va_start(ptr %a)
  %gp_offset_p = getelementptr inbounds %struct.__va_list_tag, ptr %a, i32 0, i32 0
  %gp_offset = load i32, ptr %gp_offset_p, align 4
  call void @llvm.va_end(ptr %a)
  ret i32 0
}

; In this test, only FPR offset (4) is read
; CHECK: define double @test_only_fpr(ptr %fmt, ...) #[[ATTR3:[0-9]+]]
define double @test_only_fpr(ptr %fmt, ...) {
entry:
  %a = alloca [1 x %struct.__va_list_tag], align 16
  call void @llvm.va_start(ptr %a)
  %fp_offset_p = getelementptr inbounds %struct.__va_list_tag, ptr %a, i32 0, i32 1
  %fp_offset = load i32, ptr %fp_offset_p, align 4
  call void @llvm.va_end(ptr %a)
  ret double 0.0
}

declare void @llvm.va_start(ptr)
declare void @llvm.va_end(ptr)

; CHECK: attributes #[[ATTR1]] = { "va_list_fpr_size"="0" "va_list_gpr_size"="0" }
; CHECK: attributes #[[ATTR2]] = { "va_list_fpr_size"="0" "va_list_gpr_size"="6" }
; CHECK: attributes #[[ATTR3]] = { "va_list_fpr_size"="8" "va_list_gpr_size"="0" }
