; ModuleID = 'testF.cpp'
source_filename = "testF.cpp"
target datalayout = "e-m:e-p:32:32-p270:32:32-p271:32:32-p272:64:64-i128:128-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-unknown-linux-gnu"

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: readwrite) uwtable
define dso_local noundef nonnull align 4 dereferenceable(12) ptr @_Z11vec3_testF1R7Float3FRKS_(ptr noundef nonnull returned align 4 dereferenceable(12) %0, ptr nocapture noundef nonnull readonly align 4 dereferenceable(12) %1) local_unnamed_addr #0 {
  %3 = load float, ptr %0, align 4, !tbaa !6, !noalias !11
  %4 = insertelement <3 x float> poison, float %3, i64 0
  %5 = getelementptr inbounds i8, ptr %0, i32 4
  %6 = getelementptr inbounds i8, ptr %0, i32 8
  %7 = load <2 x float>, ptr %5, align 4, !tbaa !14, !noalias !11
  %8 = shufflevector <2 x float> %7, <2 x float> poison, <3 x i32> <i32 0, i32 1, i32 poison>
  %9 = shufflevector <3 x float> %4, <3 x float> %8, <3 x i32> <i32 0, i32 3, i32 4>
  %10 = load float, ptr %1, align 4, !tbaa !6, !noalias !11
  %11 = insertelement <3 x float> poison, float %10, i64 0
  %12 = getelementptr inbounds i8, ptr %1, i32 4
  %13 = load <2 x float>, ptr %12, align 4, !tbaa !14, !noalias !11
  %14 = shufflevector <2 x float> %13, <2 x float> poison, <3 x i32> <i32 0, i32 1, i32 poison>
  %15 = shufflevector <3 x float> %11, <3 x float> %14, <3 x i32> <i32 0, i32 3, i32 4>
  %16 = fadd <3 x float> %9, %15
  %17 = extractelement <3 x float> %16, i64 2
  %18 = shufflevector <3 x float> %16, <3 x float> poison, <2 x i32> <i32 0, i32 1>
  store <2 x float> %18, ptr %0, align 4, !tbaa !14
  store float %17, ptr %6, align 4, !tbaa !14
  ret ptr %0
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: readwrite) uwtable "min-legal-vector-width"="96" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"NumRegisterParameters", i32 0}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = !{!"Apple clang version 17.0.0 (clang-1700.6.4.2)"}
!6 = !{!7, !8, i64 0}
!7 = !{!"_ZTS7Float3F", !8, i64 0, !8, i64 4, !8, i64 8}
!8 = !{!"float", !9, i64 0}
!9 = !{!"omnipotent char", !10, i64 0}
!10 = !{!"Simple C++ TBAA"}
!11 = !{!12}
!12 = distinct !{!12, !13, !"_ZNK7Float3FplERKS_: argument 0"}
!13 = distinct !{!13, !"_ZNK7Float3FplERKS_"}
!14 = !{!8, !8, i64 0}
