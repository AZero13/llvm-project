struct S {
  __attribute__((visibility("hidden"))) virtual void doStuff();
};
void test() {
  S *s = new S;
  s->doStuff();
}
