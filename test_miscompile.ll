define i16 @test_miscompile(i16 %a, i32 %b) {
  %aext = sext i16 %a to i64
  %bext = sext i32 %b to i64
  %sub = sub i64 %aext, %bext
  %abs = call i64 @llvm.abs.i64(i64 %sub, i1 false)
  %nabs = sub i64 0, %abs
  %trunc = trunc i64 %nabs to i16
  ret i16 %trunc
}

; Expected behavior:
; - %abs is always non-negative (absolute value)
; - %nabs is always negative (0 - abs)
; - %trunc should be the negative absolute value truncated to 16 bits
;
; But the generated assembly does:
; sxth w8, w0
; subs w8, w8, w1
; cneg w0, w8, gt
; ret
;
; This is equivalent to:
; if (a > b) return -(a-b) else return (a-b)
; Which is completely wrong!
;
; ISSUE: The expandABS function was transforming 0 - abs(x) into smin(x, sub(0,x)),
; but this pattern was getting incorrectly matched by the AArch64 backend to
; generate conditional logic that can return positive values.
;
; FIX: Modified expandABS to use the shift-based abs expansion for 0 - abs(x)
; instead of smin(x, sub(0,x)) to avoid pattern matching issues.
