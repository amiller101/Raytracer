#pragma once
#include "vec3.h"

class Ray {

    Vec3 origin;
    Vec3 dir;

    Ray() {}
    Ray(const Vec3& origin, const Vec3& dir){
        this->origin = origin; this->dir = dir;
    }

    Vec3 at(double t) const {
        return origin + (dir * t);
    }

};