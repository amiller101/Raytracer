//tells compiler to only include this header file once, even if you write #include several places
//Modern replacement for the more classic #ifndef VEC3_h <newline> #def<VEC3_H> <code here> #endif
#pragma once
#include <cmath>
#include <iostream>

using point3 = Vec3;

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

    //the following is a series of operator definitions and overloads for the vec3 class
    //Vec3 is passed in as a const ref to Vec3 so that we don't have to create a copy of the variable each time (wastes space and time),
    //yet we enforce using it AS IF it were just a copy of Vec3 (cannot alter).

    //Addition
    Vec3 operator+(const Vec3 &summand) const {
        return Vec3(
        this->x + summand.x,
        this->y + summand.y,
        this->z + summand.z
        );
    }
    
    //In-place Addition
    Vec3& operator+=(const Vec3 &summand) {
        this->x += summand.x;
        this->y += summand.y;
        this->z += summand.z;
        return *this;
    }

    //Scalar multiplication
    Vec3 operator*(const double scalar) const {
        return Vec3(
        x * scalar,
        y * scalar,
        z * scalar
        );
    }

    //In-place Scalar multiplication
    Vec3& operator*=(const double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    //Dot Product
    double operator*(const Vec3& other) const {
        return
            (this->x * other.x +
            this->y * other.y +
            this->z * other.z);
    }

    //Negation
    Vec3 operator-() const { 
        return Vec3(
            -(this->x),
            -(this->y),
            -(this->z)
        );
    }
    //Subtraction
    Vec3 operator-(const Vec3 subtrahend) const {
        return Vec3(
            this->x - subtrahend.x,
            this->y - subtrahend.y,
            this->z - subtrahend.z
        );
    }

    //In-place subtraction
    Vec3& operator-=(const Vec3& subtrahend) {
        this->x -= subtrahend.x;
        this->y -= subtrahend.y;
        this->z -= subtrahend.z;
        return *this;
    }

    //Scalar division
    Vec3 operator/(const double t) const { return (Vec3(*this) * (1/t)); }

    //In-place scalar division
    Vec3& operator/=(double t) { return *this *= 1/t; }

    double length() const { return std::sqrt(length_squared()); }
    double length_squared() const { return ((*this)*(*this)); }

    static Vec3 unit_vector(const Vec3& vec)
    {
        return Vec3(vec/vec.length());
    }

};

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.x << " " << v.y << " " << v.z;
}
