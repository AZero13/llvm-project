#include <stdio.h>
#include <stdlib.h>

// Function that should compute 0 - abs(a - b)
int test_function(int a, int b) {
    int diff = a - b;
    int abs_diff = abs(diff);
    return 0 - abs_diff;
}

// Manual implementation using the assembly logic
int manual_implementation(int a, int b) {
    int diff = a - b;
    // cneg logic: if diff >= 0, return -diff, else return diff
    return (diff >= 0) ? -diff : diff;
}

int main() {
    int test_cases[][2] = {
        {5, 3},   // diff = 2, abs = 2, result = -2
        {3, 5},   // diff = -2, abs = 2, result = -2
        {5, 5},   // diff = 0, abs = 0, result = 0
        {-5, -3}, // diff = -2, abs = 2, result = -2
        {-3, -5}, // diff = 2, abs = 2, result = -2
    };
    
    for (int i = 0; i < 5; i++) {
        int a = test_cases[i][0];
        int b = test_cases[i][1];
        int expected = test_function(a, b);
        int manual = manual_implementation(a, b);
        
        printf("a=%d, b=%d: expected=%d, manual=%d %s\n", 
               a, b, expected, manual, 
               expected == manual ? "✓" : "✗");
    }
    
    return 0;
}
