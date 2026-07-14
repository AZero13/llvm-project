struct Float3E {
    float x;
    float y;
    float z;
};
void add(Float3E* __restrict a, Float3E* __restrict b, Float3E* __restrict c) {
    for (int i=0; i<1024; ++i) {
        c[i].x = a[i].x + b[i].x;
        c[i].y = a[i].y + b[i].y;
        c[i].z = a[i].z + b[i].z;
    }
}
