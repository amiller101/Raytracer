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

class dielectric : public material {
  public:
    dielectric(double refraction_index) : refraction_index(refraction_index) {}

    bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override {
      attenuation = color(1.0, 1.0, 1.0);
      double ri = rec.front_face ? (1.0/refraction_index) : refraction_index;

      Vec3 unit_direction = unit_vector(r_in.direction);
      //check for total internal reflection
      double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
      double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

      bool cannot_refract = ri * sin_theta > 1.0;
      Vec3 direction;

      if (cannot_refract || random_double() < reflectance(cos_theta, ri))
      {
        direction = reflect(unit_direction, rec.normal);
      }
      else
      {
        direction = refract(unit_direction, rec.normal, ri);
      }
      scattered = Ray(rec.collision, direction);
      return true;
    }

  private:
    // Refractive index in vacuum/air, or the ratio of the material's refractive index over refractive index of the encasing media.
    double refraction_index;
    
    //Uses Schlick's approximation for reflectance
    static double reflectance(double cos_angle_incidence, double refractive_indices_ratio) {
      auto t = (1 - refractive_indices_ratio) / (1 + refractive_indices_ratio);
      t *= t;
      return t + (1-t)*std::pow((1 - cos_angle_incidence),5);
    }
  
};