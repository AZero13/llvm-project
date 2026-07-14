#include <stdint.h>
#include <stdlib.h>
#include <utility>

template <typename T, size_t count, bool is_aligned>
struct $vec_impl {
    using type __attribute__((__vector_size__(count * sizeof(T)), __aligned__(alignof(T)))) = T;
};

template <typename T, size_t count>
struct $vec_impl<T, count, true> {
    using type __attribute__((__vector_size__(count * sizeof(T)))) = T;
};

template <typename T, size_t count, bool is_aligned = false>
using vec = $vec_impl<T, count, is_aligned>::type;

template <typename T, size_t count>
using ext_vec = T __attribute__((ext_vector_type(count)));

// Technique A: Use a vec<float, 4> loaded in parts
struct Float3A {
    float x;
    float y;
    float z;

    constexpr Float3A() = default;
    constexpr Float3A(const Float3A&) = default;
    constexpr Float3A(Float3A&&) = default;
    constexpr Float3A& operator=(const Float3A&) = default;
    constexpr Float3A& operator=(Float3A&&) = default;

    constexpr Float3A(vec<float, 4> vector) : x(vector[0]), y(vector[1]), z(vector[2]) {}
    constexpr Float3A& operator=(vec<float, 4> vector) {
        this->x = vector[0];
        this->y = vector[1];
        this->z = vector[2];
        return *this;
    }

    constexpr vec<float, 4> as_vec() const {
        return { this->x, this->y, this->z };
    }

    constexpr Float3A operator+(const Float3A& rhs) const {
        return this->as_vec() + rhs.as_vec();
    }

    constexpr Float3A& operator+=(const Float3A& rhs) {
        *this = *this + rhs;
        return *this;
    }
};

__attribute__((regparm(2),target("sse2")))
Float3A& vec3_testA1(Float3A& lhs, const Float3A& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("ssse3")))
Float3A& vec3_testA2(Float3A& lhs, const Float3A& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("sse4.1")))
Float3A& vec3_testA3(Float3A& lhs, const Float3A& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("arch=bdver3"))) // AVX
Float3A& vec3_testA4(Float3A& lhs, const Float3A& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("arch=znver5"))) // AVX512
Float3A& vec3_testA5(Float3A& lhs, const Float3A& rhs) {
    lhs += rhs;
    return lhs;
}

// Technique B: Use a vec<float, 4> with a gap in the middle
struct Float3B {
    float x;
    float y;
    float z;

    constexpr Float3B() = default;
    constexpr Float3B(const Float3B&) = default;
    constexpr Float3B(Float3B&&) = default;
    constexpr Float3B& operator=(const Float3B&) = default;
    constexpr Float3B& operator=(Float3B&&) = default;

    constexpr Float3B(vec<float, 4> vector) : x(vector[0]), y(vector[2]), z(vector[3]) {}
    constexpr Float3B& operator=(vec<float, 4> vector) {
        this->x = vector[0];
        this->y = vector[2];
        this->z = vector[3];
        return *this;
    }

    constexpr vec<float, 4> as_vec() const {
        return { this->x, 0.0f, this->y, this->z };
    }

    constexpr Float3B operator+(const Float3B& rhs) const {
        return this->as_vec() + rhs.as_vec();
    }

    constexpr Float3B& operator+=(const Float3B& rhs) {
        *this = *this + rhs;
        return *this;
    }
};

__attribute__((regparm(2),target("sse2")))
Float3B& vec3_testB1(Float3B& lhs, const Float3B& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("ssse3")))
Float3B& vec3_testB2(Float3B& lhs, const Float3B& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("sse4.1")))
Float3B& vec3_testB3(Float3B& lhs, const Float3B& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("arch=bdver3"))) // AVX
Float3B& vec3_testB4(Float3B& lhs, const Float3B& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("arch=znver5"))) // AVX512
Float3B& vec3_testB5(Float3B& lhs, const Float3B& rhs) {
    lhs += rhs;
    return lhs;
}

// Technique C: Use masked loads/stores
struct Float3C {
    float x;
    float y;
    float z;

    constexpr Float3C() = default;
    constexpr Float3C(const Float3C&) = default;
    constexpr Float3C(Float3C&& rhs) = default;
    constexpr Float3C& operator=(const Float3C&) = default;
    constexpr Float3C& operator=(Float3C&& rhs) = default;

    static inline constexpr ext_vec<bool, 4> MASK = { true, true, true, false };

    constexpr Float3C(vec<float, 4> vector) {
        __builtin_masked_store(MASK, vector, (float*)this);
    }
    constexpr Float3C& operator=(vec<float, 4> vector) {
        __builtin_masked_store(MASK, vector, (float*)this);
        return *this;
    }

    constexpr vec<float, 4> as_vec() const {
        return __builtin_masked_load(MASK, (float*)this);
    }

    // if this returns Float3C it generates an extra copy on the stack
    constexpr vec<float, 4> operator+(const Float3C& rhs) const {
        return this->as_vec() + rhs.as_vec();
    }

    constexpr Float3C& operator+=(const Float3C& rhs) {
        *this = *this + rhs;
        return *this;
    }
};

__attribute__((regparm(2),target("sse2")))
Float3C& vec3_testC1(Float3C& lhs, const Float3C& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("ssse3")))
Float3C& vec3_testC2(Float3C& lhs, const Float3C& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("sse4.1")))
Float3C& vec3_testC3(Float3C& lhs, const Float3C& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("arch=bdver3"))) // AVX
Float3C& vec3_testC4(Float3C& lhs, const Float3C& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("arch=znver5"))) // AVX512
Float3C& vec3_testC5(Float3C& lhs, const Float3C& rhs) {
    lhs += rhs;
    return lhs;
}

// Technique D: Use a mix of scalar/vector ops
struct Float3D {
    float x;
    float y;
    float z;

    constexpr Float3D() = default;
    constexpr Float3D(const Float3D&) = default;
    constexpr Float3D(Float3D&& rhs) = default;
    constexpr Float3D& operator=(const Float3D&) = default;
    constexpr Float3D& operator=(Float3D&& rhs) = default;

    constexpr Float3D(float x, vec<float, 2> vector) : x(x), y(vector[0]), z(vector[1]) {}

    constexpr std::pair<float, vec<float, 2>> as_vec() const {
        return std::make_pair(this->x, (vec<float, 2, true>){ this->y, this->z });
    }

    constexpr Float3D operator+(const Float3D& rhs) const {
        auto [x_lhs, vector_lhs] = this->as_vec();
        auto [x_rhs, vector_rhs] = rhs.as_vec();
        return { x_lhs + x_rhs, vector_lhs + vector_rhs };
    }

    constexpr Float3D& operator+=(const Float3D& rhs) {
        *this = *this + rhs;
        return *this;
    }
};

__attribute__((regparm(2),target("sse2")))
Float3D& vec3_testD1(Float3D& lhs, const Float3D& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("ssse3")))
Float3D& vec3_testD2(Float3D& lhs, const Float3D& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("sse4.1")))
Float3D& vec3_testD3(Float3D& lhs, const Float3D& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("arch=bdver3"))) // AVX
Float3D& vec3_testD4(Float3D& lhs, const Float3D& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("arch=znver5"))) // AVX512
Float3D& vec3_testD5(Float3D& lhs, const Float3D& rhs) {
    lhs += rhs;
    return lhs;
}

// Technique E: Use purely scalar ops
struct Float3E {
    float x;
    float y;
    float z;

    constexpr Float3E() = default;
    constexpr Float3E(const Float3E&) = default;
    constexpr Float3E(Float3E&& rhs) = default;
    constexpr Float3E& operator=(const Float3E&) = default;
    constexpr Float3E& operator=(Float3E&& rhs) = default;

    constexpr Float3E(float x, float y, float z) : x(x), y(y), z(z) {}

    constexpr Float3E operator+(const Float3E& rhs) const {
        return {
            this->x + rhs.x,
            this->y + rhs.y,
            this->z + rhs.z
        };
    }

    constexpr Float3E& operator+=(const Float3E& rhs) {
        *this = *this + rhs;
        return *this;
    }
};

__attribute__((regparm(2),target("sse2")))
Float3E& vec3_testE1(Float3E& lhs, const Float3E& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("ssse3")))
Float3E& vec3_testE2(Float3E& lhs, const Float3E& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("sse4.1")))
Float3E& vec3_testE3(Float3E& lhs, const Float3E& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("arch=bdver3"))) // AVX
Float3E& vec3_testE4(Float3E& lhs, const Float3E& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("arch=znver5"))) // AVX512
Float3E& vec3_testE5(Float3E& lhs, const Float3E& rhs) {
    lhs += rhs;
    return lhs;
}

// Technique F: Use ext_vec with length 3 (codegen is consistently like technique A)
struct Float3F {
    float x;
    float y;
    float z;

    constexpr Float3F() = default;
    constexpr Float3F(const Float3F&) = default;
    constexpr Float3F(Float3F&& rhs) = default;
    constexpr Float3F& operator=(const Float3F&) = default;
    constexpr Float3F& operator=(Float3F&& rhs) = default;

    constexpr Float3F(ext_vec<float, 3> vector) : x(vector.x), y(vector.y), z(vector.z) {}
    constexpr Float3F& operator=(ext_vec<float, 3> vector) {
        this->x = vector.x;
        this->y = vector.y;
        this->z = vector.z;
        return *this;
    }

    constexpr ext_vec<float, 3> as_vec() const {
        return { this->x, this->y, this->z };
    }

    constexpr Float3F operator+(const Float3F& rhs) const {
        return this->as_vec() + rhs.as_vec();
    }

    constexpr Float3F& operator+=(const Float3F& rhs) {
        *this = *this + rhs;
        return *this;
    }
};

__attribute__((regparm(2),target("sse2")))
Float3F& vec3_testF1(Float3F& lhs, const Float3F& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("ssse3")))
Float3F& vec3_testF2(Float3F& lhs, const Float3F& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("sse4.1")))
Float3F& vec3_testF3(Float3F& lhs, const Float3F& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("arch=bdver3"))) // AVX
Float3F& vec3_testF4(Float3F& lhs, const Float3F& rhs) {
    lhs += rhs;
    return lhs;
}
__attribute__((regparm(2),target("arch=znver5"))) // AVX512
Float3F& vec3_testF5(Float3F& lhs, const Float3F& rhs) {
    lhs += rhs;
    return lhs;
}
