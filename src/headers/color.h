#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

using color = vec3;

namespace raytracer
{
    inline double linear_to_gamma(double linear_component)
    {
        if (linear_component > 0)
            return sqrt(linear_component);

        return 0;
    }

    // Utility function that writes a single pixel's color out to the standard output stream.
    // This accepts on ostream so there's a single consistent interface for:
    // - writing to a file std:ofstream
    // - writing to the console std::cout
    void write_color(std::ostream &out, const color &pixel_color)
    {
        auto r = pixel_color.x();
        auto g = pixel_color.y();
        auto b = pixel_color.z();
        // Apply a linear to gamma transform for gamma 2
        r = linear_to_gamma(r);
        g = linear_to_gamma(g);
        b = linear_to_gamma(b);

        // Write the color as an integer value from 0 to 255
        // Vectors are in the range of 0 to 1, so we multiply by 255.999
        // to get the range of 0 to 255
        out << static_cast<int>(255.999 * r) << ' '
            << static_cast<int>(255.999 * g) << ' '
            << static_cast<int>(255.999 * b) << '\n';
    }

}
#endif