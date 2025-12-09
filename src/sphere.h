#pragma once

#include "utility.h"
#include "hittable.h"

//std::fmax() & std::fmin() are C++ standard functions

class Sphere : public hittable
{
    using PosFunc = point3 (*)(double t, const point3& origin);
    PosFunc pos_func;

    static point3 static_position(double /*t*/, const point3& origin)
    {
        return origin;
    }
    
    Vec3 cur_pos(double t) const {
        return pos_func(t, center);
    }

    public:
    // Sphere may be instantiated with a position function that determines where it's center is rendered at for an input t and t_0 = origin.
    // This could be fairly easily expanded to other objects, just add pos_func to hittable and have each child class implement the "center" translation differently
    // in the hit function.
    Sphere(const Vec3& center, double radius, shared_ptr<material> mat) : center(center), radius(std::fmax(0, radius)), pos_func(static_position), mat(mat) {}
    Sphere(const Vec3& center, double radius, PosFunc pos_func, shared_ptr<material> mat)
        : center(center), radius(std::fmax(0, radius)), pos_func(pos_func), mat(mat) {}

        
    

    //solves quadratic formula for time t and store's hit data in rec.
    //Uses b = -2h to simplify quadratic formula.
    bool hit(const Ray& r, interval ray_t, hit_record& rec) const override
    {
        point3 current_center = cur_pos(r.time);
        Vec3 oc = current_center - r.origin;
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
        Vec3 outward_normal = (rec.collision - current_center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;

        return true;
    }

    private:
    Vec3 center;
    double radius;
    shared_ptr<material> mat;

};
