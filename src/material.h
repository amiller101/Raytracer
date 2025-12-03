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
        attenuation = albedo;
        return true;
    }

  private:
    color albedo;
};

class specular :public material {
  public:
    specular(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override {
        //calculate reflection
        Vec3 reflected = reflect(r_in.direction, rec.normal);
        //add fuzziness
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
        scattered = Ray(rec.collision, reflected);
        attenuation = albedo;
        //ignore ray if fuzziness offest sends it through the object of original ray incidence.
        return (dot(reflected, rec.normal) > 0);
    }

  private:
    color albedo;
    double fuzz;
};