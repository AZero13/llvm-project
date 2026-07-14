#include <stdio.h>
typedef float float3 __attribute__((ext_vector_type(3)));
int main() {
    printf("sizeof: %zu, alignof: %zu\n", sizeof(float3), alignof(float3));
}
