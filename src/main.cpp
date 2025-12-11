#include "utility.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "texture.h"
#include "triangle.h"
#include "camera.h"
#include "bvh.h"
#include "quad.h"


void bouncing_spheres() {
    
    hittable_list world;
    
    auto checker = make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));
    auto checker_material = make_shared<lambertian>(checker);
    world.add(make_shared<Sphere>(point3(0,-1000,0), 1000, checker_material));

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

    world = hittable_list(make_shared<BVH_Node>(world));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1200;
    cam.samples_per_pixel = 20;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.position = point3(13,2,3);
    cam.direction   = point3(0,0,0);
    cam.up      = Vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    cam.render(world);
    

}


void checkered_spheres() {
    hittable_list world;

    auto checker = make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));

    world.add(make_shared<Sphere>(point3(0,-10, 0), 10, make_shared<lambertian>(checker)));
    world.add(make_shared<Sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.position = point3(13,2,3);
    cam.direction   = point3(0,0,0);
    cam.up      = Vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);


}


void earth() {
    auto earth_texture = make_shared<image_texture>("earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<Sphere>(point3(1,0,0), 2, earth_surface);

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.position = point3(0,0,12);
    cam.direction   = point3(0,0,0);
    cam.up      = Vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(hittable_list(globe));
}

void triangles() {
    hittable_list world;

    auto earth_texture = make_shared<image_texture>("earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    //world.add(make_shared<Sphere>(point3(0,0, -4), 0.5, make_shared<lambertian>(color(1, 0, 0))));
    world.add(make_shared<Triangle>(point3(-0.5, -0.5, -3.0), point3(0.5, -0.5, -6.0), point3(0.0, 0.5, -4.0), earth_surface));

    world.add(make_shared<Sphere>(point3(0,-1, -4), 0.5, make_shared<lambertian>(color(0, 1, 0))));
    world.add(make_shared<Sphere>(point3(1,1, -4), 0.5, make_shared<lambertian>(color(0, 0, 1))));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    cam.vfov     = 40;
    cam.position = point3(0,0,0);
    cam.direction  = point3(0,0,-1);
    cam.up      = Vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}


void quads() {
    hittable_list world;

    // Materials
    auto material3 = make_shared<specular>(color(0.8, 0.85, 0.8), 0);
    auto left_red     = make_shared<lambertian>(color(1.0, 0.2, 0.2));
    auto back_green   = make_shared<lambertian>(color(0.2, 1.0, 0.2));
    auto right_blue   = make_shared<lambertian>(color(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<lambertian>(color(1.0, 0.5, 0.0));
    auto lower_teal   = make_shared<lambertian>(color(0.2, 0.8, 0.8));

    auto earth_texture = make_shared<image_texture>("earthmap.jpg");
    auto earth_surface = make_shared<specular>(earth_texture, 0.0);

    // Quads
    world.add(make_shared<quad>(point3(-3,-2, 5), Vec3(0, 0,-4), Vec3(0, 4, 0), material3));
    world.add(make_shared<quad>(point3(-2,-2, 0), Vec3(4, 0, 0), Vec3(0, 4, 0), material3));
    world.add(make_shared<quad>(point3( 3,-2, 1), Vec3(0, 0, 4), Vec3(0, 4, 0), material3));
    world.add(make_shared<quad>(point3(-2, 3, 1), Vec3(4, 0, 0), Vec3(0, 0, 4), material3));
    world.add(make_shared<quad>(point3(-2,-3, 5), Vec3(4, 0, 0), Vec3(0, 0,-4), material3));
    world.add(make_shared<Sphere>(point3(0, 0, 0), 1.5, earth_surface));
    world.add(make_shared<Sphere>(point3(-2.0, 0, 0), 0.5, upper_orange));


    

    Camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;//100
    cam.max_depth         = 50;//50

    cam.vfov     = 80; //80
    cam.position = point3(0,0,9);
    cam.direction   = point3(0,0,0);
    cam.up      = Vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}


int main()
{
    switch(5) {
        case 1: bouncing_spheres(); break;
        case 2: checkered_spheres(); break;
        case 3: earth(); break;
        case 4: triangles(); break;
        case 5: quads(); break;
    }
}
