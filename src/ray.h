#pragma once
#include "vec3.h"

using point3 = Vec3;

class Ray {

    public:
    Vec3 origin;
    Vec3 direction;

    Ray() {}
    Ray(const Vec3& origin, const Vec3& dir){
        this->origin = origin; this->direction = dir;
    }

    Vec3 at(double t) const {
        return origin + (direction * t);
    }

};