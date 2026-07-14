define void @add3_ptr(ptr %a, ptr %b, ptr %c) {
  %va = load <3 x float>, ptr %a, align 4
  %vb = load <3 x float>, ptr %b, align 4
  %vadd = fadd <3 x float> %va, %vb
  store <3 x float> %vadd, ptr %c, align 4
  ret void
}
