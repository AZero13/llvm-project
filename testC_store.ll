define void @store3(ptr %p, <4 x float> %v) {
  call void @llvm.masked.store.v4f32.p0(<4 x float> %v, ptr %p, i32 4, <4 x i1> <i1 true, i1 true, i1 true, i1 false>)
  ret void
}
declare void @llvm.masked.store.v4f32.p0(<4 x float>, ptr, i32, <4 x i1>)
