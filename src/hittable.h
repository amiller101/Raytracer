#pragma once
#include "utility.h"
#include "bounding_box.h"

class material;

class hit_record
{
    public:
    Vec3 collision;
    Vec3 normal;
    shared_ptr<material> mat;
    double t;
    bool front_face;

    void set_face_normal(const Ray& r, const Vec3& outward_normal)
    {
        //if positive, then vectors coincide direction and ray is leaving the object (from within)
        front_face = dot(r.direction, outward_normal) < 0;   
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable
{
    public:
    virtual ~hittable() = default;

    //with check for hits over time interval [t_min, t_max], store any hits into the hit_records data array||object
    virtual bool hit(const Ray& r, interval ray_t, hit_record& rec) const = 0;

    virtual Bounding_Box bounding_box() const = 0;
};