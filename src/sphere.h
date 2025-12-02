#pragma once

#include "utility.h"
#include "hittable.h"

//std::fmax() & std::fmin() are C++ standard functions

class Sphere : public hittable
{
    public:
    Sphere(const Vec3& center, double radius, shared_ptr<material> mat) : center(center), radius(std::fmax(0, radius)), mat(mat) {
        //TODO init material pointer 'mat'
    }

    //solves quadratic formula for time t and store's hit data in rec.
    //Uses b = -2h to simplify quadratic formula.
    bool hit(const Ray& r, interval ray_t, hit_record& rec) const override
    {
        Vec3 oc = center - r.origin;
        auto a = r.direction.length_squared();
        auto h = dot(r.direction, oc);
        auto c = oc.length_squared() - radius*radius;
        auto discriminant = h*h - a*c;

        if (discriminant < 0) {
            return false;
        }

        auto sqrtd = std::sqrt(discriminant);

        //find the nearest root in the given time range
        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                return false;
            }   
        }

        rec.t = root;
        rec.collision = r.at(rec.t);
        //div by radius normalizes
        Vec3 outward_normal = (rec.collision - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;

        return true;
    }

    private:
    Vec3 center;
    double radius;
    shared_ptr<material> mat;
};
