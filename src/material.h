#pragma once

#include "hittable.h"

class material {
    public:
    virtual ~material() = default;

    //input: incoming ray, hit record data including the collision normal (defines reflectance behavior)
    //output: color of the material hit, reflected ray
    virtual bool scatter(const Ray& ray_in, const hit_record& rec, color& attenuation, Ray& scattered) const {
        return false;
    }

};

class lambertian : public material{
  public:
    lambertian(const color& albedo) : albedo(albedo) {}

    //Returns true because it always reflects. 
    bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        //Catch edge-case scatter direction
        if (scatter_direction.near_zero())
        {
            scatter_direction = rec.normal;
        }

        scattered = Ray(rec.collision, scatter_direction);
        return true;
    }

  private:
    color albedo;
};