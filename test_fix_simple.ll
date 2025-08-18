define i32 @test_fix_simple(i32 %a, i32 %b) {
  %sub = sub i32 %a, %b
  %abs = call i32 @llvm.abs.i32(i32 %sub, i1 false)
  %nabs = sub i32 0, %abs
  ret i32 %nabs
}

; This should now generate correct code that always returns a negative value
; The fix avoids the problematic smin(x, sub(0,x)) pattern that was getting
; incorrectly matched by the AArch64 backend
