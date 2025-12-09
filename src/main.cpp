#include "utility.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"

int main() {
    
    hittable_list world;
    
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random_vector() * random_vector();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random_vector(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<specular>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<specular>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1200;
    cam.samples_per_pixel = 10;
    cam.max_depth         = 20;

    cam.vfov     = 20;
    cam.position = point3(13,2,3);
    cam.direction   = point3(0,0,0);
    cam.up      = Vec3(0,1,0);

    cam.render(world);

    /*
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.50);
    auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
    auto material_right  = make_shared<specular>(color(0.8, 0.6, 0.2), 0.2);

    world.add(make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
    world.add(make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    world.add(make_shared<Triangle>(point3(-1.0, 0.0, -1.0), point3(0.0, .6, -2.0), point3(1.0, 0.0, -1.0), material_right));






    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    cam.vfov = 60;
    cam.position = point3(-2, 2, 1);
    cam.direction = point3(0, 0, -1);
    cam.up = Vec3(0, 1, 0);

    cam.render(world);
    */
}
