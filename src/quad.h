#pragma once

#include "hittable.h"

class quad: public hittable {
    public:

    quad(const point3& Q, const Vec3 u, const Vec3 v, shared_ptr<material> mat) : Q(Q), u(u), v(v), mat(mat) {
        auto n = cross(u, v);
        normal = unit_vector(n);
        D = dot(normal, Q);
        w = n / dot (n, n);
    }

    virtual void set_bounding_box() {
        auto bbox_diag1 = Bounding_Box(Q, Q + u + v);
        auto bbox_diag2 = Bounding_Box(Q + u, Q + v);
        bbox = Bounding_Box(bbox_diag1, bbox_diag2);
    }
    Bounding_Box bounding_box() const override {return bbox;}

    bool hit(const Ray& r, interval ray_t, hit_record& rec) const override {
        //if ray is tangent to the bounding plane, miss
        if (std::fabs(dot(r.direction, normal)) < 1e-8)
        {
            return false;
        }

        auto t = (D - dot(normal,r.origin))/dot(normal, r.direction);

        if (!ray_t.contains(t))
        {
            return false;
        }

        auto intersection = r.at(t);

        //create quad coord system with basis vectors uv
        auto relative_point = intersection - Q;
        auto alpha = dot(w, cross(relative_point, v));
        auto beta = dot(w, cross(u, relative_point));

        if(!is_interior(alpha, beta, rec))
            return false;

        rec.collision = intersection;
        rec.t = t;
        rec.mat = mat;
        rec.set_face_normal(r, normal);

        return true;
    }

    //given the hit point in plane coords, return false is it is
    //outside the primitive bounded by vectors a and b.
    //otherwise set UV coords and return true.
    virtual bool is_interior(double a, double b, hit_record& rec) const {
        interval unit_interval = interval(0, 1);
        if (!unit_interval.contains(a) || !unit_interval.contains(b))
            return false;

        rec.u = a;
        rec.v = b;
        return true;
    }

    private:
    point3 Q;
    Vec3 u;
    Vec3 v;
    Vec3 normal;
    shared_ptr<material> mat;
    Bounding_Box bbox;
    double D;
    Vec3 w;

};