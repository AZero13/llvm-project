template <typename T> using vec = T __attribute__((ext_vector_type(4)));

struct Float3A {
    float x, y, z;
    constexpr Float3A(vec<float> v) : x(v[0]), y(v[1]), z(v[2]) {}
    constexpr vec<float> as_vec() const { return {x, y, z, 0.0f}; }
};

struct Float3B {
    float x, y, z;
    constexpr Float3B(vec<float> v) : x(v[0]), y(v[2]), z(v[3]) {}
    constexpr vec<float> as_vec() const { return {x, 0.0f, y, z}; }
};
