define <4 x float> @load3(ptr %p) {
  %v = call <4 x float> @llvm.masked.load.v4f32.p0(ptr %p, i32 4, <4 x i1> <i1 true, i1 true, i1 true, i1 false>, <4 x float> poison)
  ret <4 x float> %v
}
declare <4 x float> @llvm.masked.load.v4f32.p0(ptr, i32, <4 x i1>, <4 x float>)
