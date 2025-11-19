#include "utility.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

//r - ray determining color
//world - list of objects the ray could hit
color ray_color(const Ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    Vec3 unit_direction = unit_vector(r.direction);
    auto a = 0.5*(unit_direction.y + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}



int main() {
    
    hittable_list world;
    world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

    Camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1400;
    cam.samples_per_pixel = 100;

    cam.render(world);
}
