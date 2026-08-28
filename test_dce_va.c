#include <stdarg.h>

int test_unused_va(int count, ...) {
    va_list args;
    va_start(args, count);
    
    if (count > 0) {
        // We extract the argument, but never use it!
        // DCE should delete this if we run late enough.
        int unused = va_arg(args, int);
    }
    
    va_end(args);
    return 0;
}
