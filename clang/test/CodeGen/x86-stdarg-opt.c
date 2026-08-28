// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -emit-llvm -O2 -mllvm -passes=optimize-stdarg %s -o - | FileCheck %s

#include <stdarg.h>

// CHECK: define dso_local void @test_no_args(ptr noundef %fmt, ...) {{.*}} #[[ATTR1:[0-9]+]]
void test_no_args(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    va_end(args);
}

// CHECK: define dso_local i32 @test_only_gpr(ptr noundef %fmt, ...) {{.*}} #[[ATTR2:[0-9]+]]
int test_only_gpr(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int x = va_arg(args, int);
    va_end(args);
    return x;
}

// CHECK: define dso_local double @test_only_fpr(ptr noundef %fmt, ...) {{.*}} #[[ATTR3:[0-9]+]]
double test_only_fpr(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    double x = va_arg(args, double);
    va_end(args);
    return x;
}

// CHECK: attributes #[[ATTR1]] = { {{.*}}"va_list_fpr_size"="0" "va_list_gpr_size"="0"{{.*}} }
// CHECK: attributes #[[ATTR2]] = { {{.*}}"va_list_fpr_size"="0" "va_list_gpr_size"="6"{{.*}} }
// CHECK: attributes #[[ATTR3]] = { {{.*}}"va_list_fpr_size"="8" "va_list_gpr_size"="0"{{.*}} }
