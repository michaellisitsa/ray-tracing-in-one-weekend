#include "headers/rtweekend.h"
#include "main.h"
#include "headers/sphere.h"
#include "headers/hittable_list.h"

color ray_color(const ray &r, int depth, const hittable &world)
{
    if (depth <= 0)
    {
        return color(0, 0, 0);
    }
    auto rec = hit_record();
    // Let's find the vertical position
    // We get this off the ray direction, but how do we know where are we in the image right now.
    // I guess if its as unit vector then it'll be from -1 to 1
    // linear blend between alpha = 1 blue, alpha = 0 white
    // blendedValue=(1−𝑎)⋅startValue+𝑎⋅endValue,
    // sphere s = sphere(point3(0, 0, -1), 0.5);
    if (world.hit(r, interval(0.001, infinity), rec))
    {
        vec3 direction = rec.normal + random_unit_vector();
        return 0.5 * ray_color(ray(rec.p, direction), depth - 1, world);
    }
    vec3 unit_direction = unit_vector(r.direction());
    double vertical_position = unit_direction.y();
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
    // ideal ratio
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 1000;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    // We need to position the camera at origin.
    auto camera_center = point3(0, 0, 0);

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Viewing direction is in the z-axis of length 1.0;
    // Which is half our viewport height
    // The viewport is the rectangle that we're projecting the image onto
    auto focal_length = 1.0;
    // What's the difference between viewport and image?
    // Viewport is a virtual rectangle in the 3d World that contains the grid of image pixel locations
    double viewport_height = 2.0;
    // Instead of using the aspect ratio, we use the image aspect ratio which is the real aspect ratio
    // To ensure the operation has a floating point result, at least one of the operands of the division must be a floating point number
    double viewport_width = viewport_height * double(image_width) / image_height;

    // Let's calculate the vectors along the horizontal and vertical starting with defining 3d points.
    auto viewport_u = vec3(viewport_width, 0, 0);
    // Negate the viewport height to make the vector point downwards
    // The ppm image format goes from top-left scanning each line from left to right top to bottom
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    // This allows us to shift across the viewport in pixel increments.
    // Note this is an element-wise division of the viewport vectors.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Now we need to offset the viewport away from the origin. i.e. the ray constant.
    // We pick the upper left point of the viewport as the starting point.
    // The focal point is offset in the z-direction
    vec3 focal_vector = vec3(0, 0, focal_length);

    // We want the center of the viewport plane to be along the z-axis.
    // Create a vector offsetting the image by -viewport_width/2 `left` and -viewport_height/2 `down`
    vec3 viewport_offset = -viewport_u / 2 - viewport_v / 2;
    auto viewport_upper_left = camera_center - focal_vector + viewport_offset;

    // We need to cast a ray into the middle of the first pixel.
    // Let's calculate its position
    // Note the v vectors are already pointing downwards, so don't need to be negated.
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // render
    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << " " << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            // Now we have the pixel location and direction that each ray needs to be cast.
            // We want to cast a ray to the pixel location, or the viewport location?
            // It doesn't really matter as we've already defined our image dimensions. We just need to be consistent.
            // We're actually working with doubles along the viewport now. We're only using the loop over image size
            // because its a convenient index for the pixel location.
            auto pixel_center = pixel00_loc + i * pixel_delta_u + j * pixel_delta_v;
            // But what's the ray got to do with this pixel location?
            // We're interested in the length of the ray from the camera to the pixel location.
            // Or we're interested in the direction of the ray relative to the normal plane of the image?
            //
            ray r = ray(camera_center, pixel_center - camera_center);
            // double r = double(i) / image_width;
            // double b = 1.0;
            color pixel_color = ray_color(r, 10, world);
            raytracer::write_color(std::cout, pixel_color);
        }
    }
}