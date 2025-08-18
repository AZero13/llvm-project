define i32 @test_debug(i32 %a, i32 %b) {
  %sub = sub i32 %a, %b
  %abs = call i32 @llvm.abs.i32(i32 %sub, i1 false)
  %nabs = sub i32 0, %abs
  ret i32 %nabs
}

; This should trigger the debugging output to see what happens
; when smin(x, sub(0,x)) gets processed
