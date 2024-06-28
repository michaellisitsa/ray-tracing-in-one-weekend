#include <iostream>
#include "headers/vec3.h"

int main()
{
    vec3 v1(1, 2, 3);
    int image_width = 250;
    int image_height = 100;

    // render
    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << " " << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            double r = double(i) / image_width;
            double g = double(j) / image_height;
            double b = 0.0;

            int ir = 255.999 * r;
            int ig = 255.999 * g;
            int ib = 255.999 * b;
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}