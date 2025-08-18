define i16 @test_exact(i16 %a, i32 %b) {
  %aext = sext i16 %a to i64
  %bext = sext i32 %b to i64
  %sub = sub i64 %aext, %bext
  %abs = call i64 @llvm.abs.i64(i64 %sub, i1 false)
  %nabs = sub i64 0, %abs
  %trunc = trunc i64 %nabs to i16
  ret i16 %trunc
}
