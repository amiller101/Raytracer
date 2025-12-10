#pragma once

#include "hittable.h"

//Axis aligned bb
class Bounding_Box {


    public:
    interval x, y, z;

    Bounding_Box() {}
    Bounding_Box(const interval& x, const interval& y, const interval& z) : x(x), y(y), z(z) {
        pad_to_minimums();
    }
    Bounding_Box(const Vec3& extremas1, const Vec3& extremas2) {
        x = (extremas1.x <= extremas2.x) ? interval(extremas1.x, extremas2.x) : interval(extremas2.x, extremas1.x); 
        y = (extremas1.y <= extremas2.y) ? interval(extremas1.y, extremas2.y) : interval(extremas2.y, extremas1.y); 
        z = (extremas1.z <= extremas2.z) ? interval(extremas1.z, extremas2.z) : interval(extremas2.z, extremas1.z);
        pad_to_minimums(); 
    }

    Bounding_Box(const Bounding_Box& a, const Bounding_Box& b)
    {
        x = interval(a.x, b.x);
        y = interval(a.y, b.y);
        z = interval(a.z, b.z);
    }

    const interval& axis_interval(int i) const
    {
        if (i == 0)
        {
            return x;
        }
        else if (i == 1)
        {
            return y;
        }
        else
        {
            return z;
        }
    }

    //returns true if hit
    //Changes ray_t to be the interval of the ray within the box, need to add &?
    bool hit(const Ray& r, interval ray_t) const
    {
        const point3& ray_origin = r.origin;
        const Vec3& ray_dir = r.direction;

        //for each coordinate
        for (int i = 0; i < 3; i++)
        {
            //check if intersection and get times
            const interval& axis = axis_interval(i);
            const double axis_direction_inv = 1.0 / ray_dir[i];

            double hit_time_1 = (axis.min - ray_origin[i]) * axis_direction_inv;
            double hit_time_2 = (axis.max - ray_origin[i]) * axis_direction_inv;

            // if hit1 = entering, hit2 = leaving
            if (hit_time_1 < hit_time_2)
            {
                // tighten ray_t for points in this bounding box
                if (hit_time_1 > ray_t.min) ray_t.min = hit_time_1;
                if (hit_time_2 < ray_t.max) ray_t.max = hit_time_2;
            }
            else // if hit2 = entering, hit1 = leaving
            {
                // tighten ray_t for points in this bounding box
                if (hit_time_2 > ray_t.min) ray_t.min = hit_time_2;
                if (hit_time_1 < ray_t.max) ray_t.max = hit_time_1;
            }

            if (ray_t.max <= ray_t.min)
                return false;

        }

        return true;
    }

    // Returns the index of the longest axis of the bounding box
    int longest_axis() const {
        if (x.size() > y.size())
            return x.size() > z.size() ? 0 : 2;
        else
            return y.size() > z.size() ? 1 : 2;
    }

    static const Bounding_Box empty, universe;

    private:
// Adjust the box so that no side is narrower than some delta, padding if necessary.
void pad_to_minimums() {

        double delta = 0.0001;
        if (x.size() < delta) x = x.expand(delta);
        if (y.size() < delta) y = y.expand(delta);
        if (z.size() < delta) z = z.expand(delta);
    }

};

const Bounding_Box Bounding_Box::empty    = Bounding_Box(interval::empty,    interval::empty,    interval::empty);
const Bounding_Box Bounding_Box::universe = Bounding_Box(interval::universe, interval::universe, interval::universe);