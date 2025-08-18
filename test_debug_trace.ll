define i32 @test_debug_trace(i32 %a, i32 %b) {
  %sub = sub i32 %a, %b
  %abs = call i32 @llvm.abs.i32(i32 %sub, i1 false)
  %nabs = sub i32 0, %abs
  ret i32 %nabs
}

; To trace this issue, we can use:
; 1. llc -debug-only=isel -o - test_debug_trace.ll
; 2. llc -debug-only=legalize-types -o - test_debug_trace.ll  
; 3. llc -debug-only=dag-combine -o - test_debug_trace.ll
