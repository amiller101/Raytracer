#pragma once
#include "vec3.h"

class Ray {

    vec3 origin;
    vec3 dir;

    Ray() {}
    Ray(const vec3& origin, const vec3& dir){
        this->origin = origin; this->dir = dir;
    }

    vec3 at(double t) const {
        return origin + (dir * t);
    }

};