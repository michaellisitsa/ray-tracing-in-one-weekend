#include "main.h"
#include "headers/vec3.h"
#include "headers/color.h"

int main()
{
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
            double b = 1.0;

            raytracer::write_color(std::cout, color(r, g, b));
        }
    }
}