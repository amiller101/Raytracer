//tells compiler to only include this header file once, even if you write #include several places
//Modern replacement for the more classic #ifndef VEC3_h <newline> #def<VEC3_H> <code here> #endif
#pragma once
#include <cmath>
#include <iostream>

using point3 = vec3;

class vec3 {
public:
    //union allows two structures to occupy the same memory. I am effectively creating a set of alias variables.
    union {
        //for geometry
        struct { double x, y, z; };
        //for color
        struct { double r, g, b; };
    };

    vec3() : x(0), y(0), z(0) {}
    vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    //the following is a series of operator definitions and overloads for the vec3 class
    //vec3 is passed in as a const ref to vec3 so that we don't have to create a copy of the variable each time (wastes space and time),
    //yet we enforce using it AS IF it were just a copy of vec3 (cannot alter).

    
    //In-place Addition
    vec3& operator+=(const vec3 &summand) {
        this->x += summand.x;
        this->y += summand.y;
        this->z += summand.z;
        return *this;
    }

    //In-place Scalar multiplication
    vec3& operator*=(const double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    //In-place subtraction
    vec3& operator-=(const vec3& subtrahend) {
        this->x -= subtrahend.x;
        this->y -= subtrahend.y;
        this->z -= subtrahend.z;
        return *this;
    }

    //In-place scalar division
    vec3& operator/=(double scalar) { 
        return *this *= 1 / scalar; 
    }

    double length() const { return std::sqrt(length_squared()); }
    double length_squared() const { return x*x + y*y + z*z; }

};

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.x << " " << v.y << " " << v.z;
}

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

// Addition
inline vec3 operator+(const vec3& a, const vec3& b) {
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

// Subtraction
inline vec3 operator-(const vec3& a, const vec3& b) {
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

// Negation
inline vec3 operator-(const vec3& v) {
    return vec3(-v.x, -v.y, -v.z);
}

// Scalar multiplication (vec * scalar)
inline vec3 operator*(const vec3& v, double scalar) {
    return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

// Scalar multiplication (scalar * vec)
inline vec3 operator*(double scalar, const vec3& v) {
    return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

// Scalar division
inline vec3 operator/(const vec3& v, double scalar) {
    return v * (1 / scalar);
}

// Dot product
inline double dot(const vec3& a, const vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

//Cross product
inline vec3 cross(const vec3& a, const vec3& b) {
    return vec3(a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

// Unit vector
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}