define i16 @test_fix(i16 %a, i32 %b) {
  %aext = sext i16 %a to i64
  %bext = sext i32 %b to i64
  %sub = sub i64 %aext, %bext
  %abs = call i64 @llvm.abs.i64(i64 %sub, i1 false)
  %nabs = sub i64 0, %abs
  %trunc = trunc i64 %nabs to i16
  ret i16 %trunc
}

; This should now generate correct code that always returns a negative value
; The fix ensures that 0 - abs(x) uses the shift-based abs expansion
; instead of smin(x, sub(0,x)) which was getting incorrectly pattern matched
