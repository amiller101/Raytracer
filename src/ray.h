#pragma once
#include "vec3.h"

using point3 = Vec3;

class Ray {

    public:
    Vec3 origin;
    Vec3 direction;
    double time;


    Ray() {}
    Ray(const Vec3& origin, const Vec3& dir, double time) : origin(origin), direction(dir), time(time) {}    
    Ray(const Vec3& origin, const Vec3& dir) : Ray(origin, dir, 0) {}


    Vec3 at(double t) const {
        return origin + (direction * t);
    }

};