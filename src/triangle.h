#pragma once

#include "utility.h"
#include "hittable.h"

#define epsilon 1e-5
#define cmpfloat(x, y) (abs(x-y) <= epsilon)
#define MIN(x, y) (cmpfloat(x, y) ? y : x)
#define MAX(x, y) (cmpfloat(x, y) ? x : y)

class Triangle : public hittable
{
    public:
    Triangle(const Vec3& a, const Vec3& b, const Vec3& c, shared_ptr<material> mat) : a(a), b(b), c(c), mat(mat) {
        normal = cross(b - a, c - a);

        interval interval_x = interval(MIN(MIN(a.x, b.x), c.x), MAX(MAX(a.x, b.x), c.x));
        interval interval_y = interval(MIN(MIN(a.y, b.y), c.y), MAX(MAX(a.y, b.y), c.y));
        interval interval_z = interval(MIN(MIN(a.z, b.z), c.z), MAX(MAX(a.z, b.z), c.z));

        bbox = Bounding_Box(
            interval_x,
            interval_y,
            interval_z
        );
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
        set_uv_coords_triangle(rec.u, rec.v, alpha, beta, upsilon);

        return true;
    }

    //set u and v by converting the 3D cartesian point into 2D uv coordinates on the triangle's surface.
    // alpha, beta, upsilon are the triangles barycentric coordinates for the point in question.
    static void set_uv_coords_triangle(double& u, double& v, const double& alpha, const double& beta, const double& upsilon)
    {
        //for the trangles vertices a, b, c
        auto a_u = 0.5; auto a_v = 1.0;
        auto b_u = 0.0; auto b_v = 0.0;
        auto c_u = 1.0; auto c_v = 0.0;


        u = a_u + beta*(b_u - a_u) + upsilon*(c_u - a_u);
        u = a_u + beta*(b_u - a_u) + upsilon*(c_u - a_u);
    }
    
    Bounding_Box bounding_box() const override { return bbox;}

    private:
    Vec3 a;
    Vec3 b;
    Vec3 c;
    Vec3 normal;
    shared_ptr<material> mat;
    Bounding_Box bbox;
};

