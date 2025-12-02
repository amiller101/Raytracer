//tells compiler to only include this header file once, even if you write #include several places
//Modern replacement for the more classic #ifndef VEC3_h <newline> #def<VEC3_H> <code here> #endif
#pragma once

//#include "utility.h"

class Vec3 {
public:
    //union allows two structures to occupy the same memory. I am effectively creating a set of alias variables.
    union {
        //for geometry
        struct { double x, y, z; };
        //for color
        struct { double r, g, b; };
    };

    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    //the following is a series of operator definitions and overloads for the Vec3 class
    //Vec3 is passed in as a const ref to Vec3 so that we don't have to create a copy of the variable each time (wastes space and time),
    //yet we enforce using it AS IF it were just a copy of Vec3 (cannot alter).

    
    //In-place Addition
    Vec3& operator+=(const Vec3 &summand) {
        this->x += summand.x;
        this->y += summand.y;
        this->z += summand.z;
        return *this;
    }

    //In-place Scalar multiplication
    Vec3& operator*=(const double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    //In-place Vector entry-wise multiplication
    //In-place Scalar multiplication
    Vec3& operator*=(const Vec3& v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    //In-place subtraction
    Vec3& operator-=(const Vec3& subtrahend) {
        this->x -= subtrahend.x;
        this->y -= subtrahend.y;
        this->z -= subtrahend.z;
        return *this;
    }

    //In-place scalar division
    Vec3& operator/=(double scalar) { 
        return *this *= 1 / scalar; 
    }

    //Returns true if near zero in all dimensions
    bool near_zero()
    {
        auto threshold = 1e-8;
        return ((std::fabs(x) < threshold) && (std::fabs(y) < threshold) && (std::fabs(z) < threshold));
    }

    double length() const { return std::sqrt(length_squared()); }
    double length_squared() const { return x*x + y*y + z*z; }

};

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.x << " " << v.y << " " << v.z;
}

// Addition
inline Vec3 operator+(const Vec3& a, const Vec3& b) {
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

// Subtraction
inline Vec3 operator-(const Vec3& a, const Vec3& b) {
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

// Negation
inline Vec3 operator-(const Vec3& v) {
    return Vec3(-v.x, -v.y, -v.z);
}

// Scalar multiplication (vec * scalar)
inline Vec3 operator*(const Vec3& v, double scalar) {
    return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

// Scalar multiplication (scalar * vec)
inline Vec3 operator*(double scalar, const Vec3& v) {
    return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

// Scalar division
inline Vec3 operator/(const Vec3& v, double scalar) {
    return v * (1 / scalar);
}

// Dot product
inline double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

//Cross product
inline Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

// Unit vector
inline Vec3 unit_vector(const Vec3& v) {
    return v / v.length();
}

//returns random vector with canonical entries
inline Vec3 random_vector() 
{
    return Vec3(random_double(), random_double(), random_double());
}

//returns random vector in [min, max)
inline Vec3 random_vector(double min, double max) 
{
    return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

//returns random unit vector
inline Vec3 random_unit_vector() {
    while (true) {
        auto p = random_vector(-1,1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

//returns a random unit vector on the hemisphere according to the input normal
inline Vec3 random_on_hemisphere(const Vec3& normal) {
    Vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}