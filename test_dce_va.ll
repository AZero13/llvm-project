; ModuleID = '/Users/main/llvm-project/test_dce_va.c'
source_filename = "/Users/main/llvm-project/test_dce_va.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i8:8:32-i16:16:32-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "aarch64-unknown-linux-gnu"

%struct.__va_list = type { ptr, ptr, ptr, i32, i32 }

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn uwtable
define dso_local noundef i32 @test_unused_va(i32 noundef %count, ...) local_unnamed_addr #0 {
entry:
  %args = alloca %struct.__va_list, align 8
  call void @llvm.lifetime.start.p0(ptr nonnull %args) #3
  call void @llvm.va_start.p0(ptr nonnull %args)
  %cmp = icmp sgt i32 %count, 0
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %gr_offs_p = getelementptr inbounds nuw i8, ptr %args, i64 24
  %gr_offs = load i32, ptr %gr_offs_p, align 8
  %0 = icmp sgt i32 %gr_offs, -1
  br i1 %0, label %vaarg.on_stack, label %vaarg.maybe_reg

vaarg.maybe_reg:                                  ; preds = %if.then
  %new_reg_offs = add nsw i32 %gr_offs, 8
  store i32 %new_reg_offs, ptr %gr_offs_p, align 8
  %inreg = icmp samesign ult i32 %gr_offs, -7
  br i1 %inreg, label %if.end, label %vaarg.on_stack

vaarg.on_stack:                                   ; preds = %vaarg.maybe_reg, %if.then
  %stack = load ptr, ptr %args, align 8
  %new_stack = getelementptr inbounds nuw i8, ptr %stack, i64 8
  store ptr %new_stack, ptr %args, align 8
  br label %if.end

if.end:                                           ; preds = %vaarg.on_stack, %vaarg.maybe_reg, %entry
  call void @llvm.va_end.p0(ptr nonnull %args)
  call void @llvm.lifetime.end.p0(ptr nonnull %args) #3
  ret i32 0
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(ptr captures(none)) #1

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn
declare void @llvm.va_start.p0(ptr) #2

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(ptr captures(none)) #1

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn
declare void @llvm.va_end.p0(ptr) #2

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn uwtable "frame-pointer"="non-leaf-no-reserve" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+fp-armv8,+neon,+v8a,-fmv" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { mustprogress nocallback nofree nosync nounwind willreturn }
attributes #3 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8, !9}
!llvm.ident = !{!10}
!llvm.errno.tbaa = !{!11}

!0 = !{i32 1, !"ptrauth-elf-got", i32 0}
!1 = !{i32 1, !"ptrauth-init-fini", i32 0}
!2 = !{i32 1, !"ptrauth-init-fini-address-discrimination", i32 0}
!3 = !{i32 1, !"ptrauth-sign-personality", i32 0}
!4 = !{i32 1, !"aarch64-elf-pauthabi-platform", i32 268435458}
!5 = !{i32 1, !"aarch64-elf-pauthabi-version", i32 0}
!6 = !{i32 8, !"PIC Level", i32 2}
!7 = !{i32 7, !"PIE Level", i32 2}
!8 = !{i32 7, !"uwtable", i32 2}
!9 = !{i32 7, !"frame-pointer", i32 4}
!10 = !{!"clang version 24.0.0git (https://github.com/AZero13/llvm-project.git 7d44a153dda3d6e1f354e1d3e94fe7c52f1102ee)"}
!11 = !{!12, !13, i64 0}
!12 = !{!"__libc_errno", !13, i64 0}
!13 = !{!"int", !14, i64 0}
!14 = !{!"omnipotent char", !15, i64 0}
!15 = !{!"Simple C/C++ TBAA"}
