#include <stdio.h>
#include <stdint.h>

// 64-bit version (what LLVM IR should do)
int16_t correct_64bit(int16_t a, int32_t b) {
    int64_t aext = (int64_t)a;
    int64_t bext = (int64_t)b;
    int64_t sub = aext - bext;
    int64_t abs_sub = (sub < 0) ? -sub : sub;
    int64_t nabs = 0 - abs_sub;
    return (int16_t)nabs;
}

// 32-bit version (what assembly does)
int16_t assembly_32bit(int16_t a, int32_t b) {
    int32_t a_extended = (int32_t)a;
    int32_t diff = a_extended - b;
    int32_t result = (diff > 0) ? -diff : diff;
    return (int16_t)result;
}

int main() {
    // Test cases that might show differences
    int16_t test_cases[][2] = {
        {32767, 32766},     // Large positive numbers
        {-32768, -32767},   // Large negative numbers
        {32767, -32768},    // Max positive - min negative (overflow in 32-bit)
        {-32768, 32767},    // Min negative - max positive (overflow in 32-bit)
        {0, 0},             // Zero case
        {1, -1},            // Simple case
        {-1, 1},            // Simple case
    };
    
    for (int i = 0; i < 7; i++) {
        int16_t a = test_cases[i][0];
        int32_t b = test_cases[i][1];
        int16_t correct = correct_64bit(a, b);
        int16_t assembly = assembly_32bit(a, b);
        
        printf("a=%d, b=%d: correct=%d, assembly=%d %s\n", 
               a, b, correct, assembly, 
               correct == assembly ? "✓" : "✗");
        
        if (correct != assembly) {
            printf("  DIFFERENCE FOUND! This shows the miscompilation.\n");
        }
    }
    
    return 0;
}
