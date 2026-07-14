; ModuleID = 'testE.cpp'
source_filename = "testE.cpp"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "arm64-apple-macosx15.0.0"

%struct.Float3E = type { float, float, float }

; Function Attrs: mustprogress nofree norecurse nosync nounwind ssp memory(argmem: readwrite) uwtable(sync)
define void @_Z3addP7Float3ES0_S0_(ptr noalias nocapture noundef readonly %0, ptr noalias nocapture noundef readonly %1, ptr noalias nocapture noundef writeonly %2) local_unnamed_addr #0 {
  br label %4

4:                                                ; preds = %4, %3
  %5 = phi i64 [ 0, %3 ], [ %12, %4 ]
  %6 = getelementptr inbounds %struct.Float3E, ptr %0, i64 %5
  %7 = load <12 x float>, ptr %6, align 4, !tbaa !6
  %8 = getelementptr inbounds %struct.Float3E, ptr %1, i64 %5
  %9 = load <12 x float>, ptr %8, align 4, !tbaa !6
  %10 = fadd <12 x float> %7, %9
  %11 = getelementptr inbounds %struct.Float3E, ptr %2, i64 %5
  store <12 x float> %10, ptr %11, align 4, !tbaa !6
  %12 = add nuw i64 %5, 4
  %13 = icmp eq i64 %12, 1024
  br i1 %13, label %14, label %4, !llvm.loop !10

14:                                               ; preds = %4
  ret void
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind ssp memory(argmem: readwrite) uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+altnzcv,+bti,+ccdp,+ccidx,+complxnum,+crc,+dit,+dotprod,+flagm,+fp-armv8,+fp16fml,+fptoint,+fullfp16,+jsconv,+lse,+neon,+pauth,+perfmon,+predres,+ras,+rcpc,+rdm,+sb,+sha2,+sha3,+specrestrict,+ssbs,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 26, i32 2]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Apple clang version 17.0.0 (clang-1700.6.4.2)"}
!6 = !{!7, !7, i64 0}
!7 = !{!"float", !8, i64 0}
!8 = !{!"omnipotent char", !9, i64 0}
!9 = !{!"Simple C++ TBAA"}
!10 = distinct !{!10, !11, !12, !13}
!11 = !{!"llvm.loop.mustprogress"}
!12 = !{!"llvm.loop.isvectorized", i32 1}
!13 = !{!"llvm.loop.unroll.runtime.disable"}
