define <2 x i1> @test4c_vec(<2 x i64> %a) {
  %l = ashr <2 x i64> %a, splat (i64 63)
  %na = sub <2 x i64> zeroinitializer, %a
  %r = lshr <2 x i64> %na, splat (i64 63)
  %signum = or <2 x i64> %l, %r
  %signum.trunc = trunc <2 x i64> %signum to <2 x i32>
  %c = icmp slt <2 x i32> %signum.trunc, splat (i32 1)
  ret <2 x i1> %c
}
