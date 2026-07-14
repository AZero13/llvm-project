typedef unsigned long size_t;
template <typename T, size_t count>
using ext_vec = T __attribute__((ext_vector_type(count)));

struct Float3F {
    float x;
    float y;
    float z;
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

Float3F& vec3_testF1(Float3F& lhs, const Float3F& rhs) {
    lhs += rhs;
    return lhs;
}
