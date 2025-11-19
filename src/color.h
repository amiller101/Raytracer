#pragma once
#include "interval.h"
#include "vec3.h"

using color = Vec3;

// Write a color to output in PPM format
inline void write_color(std::ostream &out, const color& pixel_color) {
    
    //Map [0, 1) to [0, 255).
    static const interval intensity(0.000, 0.999);
    int rbyte = static_cast<int>(255.999 * intensity.clamp(pixel_color.r));
    int gbyte = static_cast<int>(255.999 * intensity.clamp(pixel_color.g));
    int bbyte = static_cast<int>(255.999 * intensity.clamp(pixel_color.b));

    std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}