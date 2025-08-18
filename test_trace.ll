define i32 @test_trace(i32 %a, i32 %b) {
  %sub = sub i32 %a, %b
  %abs = call i32 @llvm.abs.i32(i32 %sub, i1 false)
  %nabs = sub i32 0, %abs
  ret i32 %nabs
}

; This should help us trace through what happens when smin(x, sub(0,x)) gets processed
