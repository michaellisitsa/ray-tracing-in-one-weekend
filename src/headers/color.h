#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

using color = vec3;

namespace raytracer
{
    // Utility function that writes a single pixel's color out to the standard output stream.
    // This accepts on ostream so there's a single consistent interface for:
    // - writing to a file std:ofstream
    // - writing to the console std::cout
    void write_color(std::ostream &out, const color &pixel_color)
    {
        // Write the color as an integer value from 0 to 255
        // Vectors are in the range of 0 to 1, so we multiply by 255.999
        // to get the range of 0 to 255
        out << static_cast<int>(255.999 * pixel_color.x()) << ' '
            << static_cast<int>(255.999 * pixel_color.y()) << ' '
            << static_cast<int>(255.999 * pixel_color.z()) << '\n';
    }

}
#endif