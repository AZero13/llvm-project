define void @store3(ptr %p, <4 x float> %v) {
  %v3 = shufflevector <4 x float> %v, <4 x float> poison, <3 x i32> <i32 0, i32 1, i32 2>
  store <3 x float> %v3, ptr %p, align 4
  ret void
}
