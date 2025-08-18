#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Function that should compute 0 - abs(a - b) with proper sign extensions
int16_t test_function(int16_t a, int32_t b) {
    int64_t aext = (int64_t)a;  // sext i16 to i64
    int64_t bext = (int64_t)b;  // sext i32 to i64
    int64_t sub = aext - bext;
    int64_t abs_sub = llabs(sub);  // abs of i64
    int64_t nabs = 0 - abs_sub;
    return (int16_t)nabs;  // trunc i64 to i16
}

// Manual implementation using the assembly logic
int16_t manual_implementation(int16_t a, int32_t b) {
    int32_t a_extended = (int32_t)a;  // sxth equivalent
    int32_t diff = a_extended - b;    // subs equivalent
    // cneg logic: if diff > 0, return -diff, else return diff
    int32_t result = (diff > 0) ? -diff : diff;
    return (int16_t)result;  // truncation
}

int main() {
    int16_t test_cases[][2] = {
        {5, 3},    // a=5, b=3: diff=2, abs=2, result=-2
        {3, 5},    // a=3, b=5: diff=-2, abs=2, result=-2
        {5, 5},    // a=5, b=5: diff=0, abs=0, result=0
        {-5, -3},  // a=-5, b=-3: diff=-2, abs=2, result=-2
        {-3, -5},  // a=-3, b=-5: diff=2, abs=2, result=-2
        {32767, 32766}, // max positive i16
        {-32768, -32767}, // min negative i16
        {0, 0},    // a=0, b=0: diff=0, abs=0, result=0
    };
    
    for (int i = 0; i < 8; i++) {
        int16_t a = test_cases[i][0];
        int32_t b = test_cases[i][1];
        int16_t expected = test_function(a, b);
        int16_t manual = manual_implementation(a, b);
        
        printf("a=%d, b=%d: expected=%d, manual=%d %s\n", 
               a, b, expected, manual, 
               expected == manual ? "✓" : "✗");
    }
    
    return 0;
}
