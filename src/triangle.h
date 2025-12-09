#pragma once

#include "utility.h"
#include "hittable.h"

#define epsilon 1e-5
#define cmpfloat(x, y) (abs(x-y) <= epsilon)

class Triangle : public hittable
{
    public:
    Triangle(const Vec3& a, const Vec3& b, const Vec3& c, shared_ptr<material> mat) : a(a), b(b), c(c), mat(mat) {
        normal = cross(b - a, c - a);
    }

    //check if hit with plane, if yes then calculate barycentric coords and check if pos, if yes then hit at intersection with plane (store in rec)
    bool hit(const Ray& r, interval ray_t, hit_record& rec) const override
    {
        //construct plane
        //a = point, normal = normal of plane

        //check for ray moving along the plane
        if (cmpfloat(dot(r.direction, normal), 0))
        {
            return false;
        }
        
        // find intersection with plane
        // t = (dot((plane_point - ray_origin), plane_normal) / dot(ray_direction, plane_normal))
        auto collision_time = dot(a - r.origin, normal) / dot(r.direction, normal);
        auto p = r.at(collision_time);

        // Calculate barycentric coordinates
        auto alpha = dot(normal, cross(c - b, p - b)) / normal.length_squared();
        auto beta = dot(normal, cross(a - c, p - c)) / normal.length_squared();
        auto upsilon = dot(normal, cross(b - a, p - a)) / normal.length_squared();

        //if any negative barycentric coord, then misses the triangle.
        if (alpha < 0 || beta < 0 || upsilon < 0)
        {
            return false;
        }

        rec.t = collision_time;
        rec.collision = p;
        rec.set_face_normal(r, unit_vector(normal));
        rec.mat = mat;

        return true;
    }

    private:
    Vec3 a;
    Vec3 b;
    Vec3 c;
    Vec3 normal;
    shared_ptr<material> mat;
};

