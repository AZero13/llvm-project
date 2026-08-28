int builtin_va_list_test(const char* str, ...) {
    __builtin_va_list a;
    int x;
    __builtin_va_start(a, str);
    x = __builtin_va_arg(a, int);
    __builtin_va_end(a);
    return x;
}
