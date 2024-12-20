#include <iostream>
#include <sstream>
#include "color.h"
#include "vec3.h"
#include "ray.h"

using namespace std;


color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
}

int main() {
    // creating the camera and viewport need this is used to
        // reconfiguring the image, so I can set its aspect ratio
        auto aspect_ratio = 16.0 / 9.0;
        int image_width = 400;

        // calculate the image height, and ensure the height is greater than one to avoid errors
        int image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        // setting up the camera adding number need to find the rays
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * double(image_width)/image_height;
        auto camera_center = point3(0,0,0);

        // Create vectors along the view port to point the rays at
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // calculate the horizontal and vertical delta, so I can use them to split the viewport into a grid.
        auto pixel_delta_u = viewport_u/ image_width;
        auto pixel_delta_v = viewport_v / image_height;

        //Calculate the locations of the upper left pixel to set as the start for the raytracing image.
        auto viewport_upper_left = camera_center -
                        vec3(0,0,focal_length) - viewport_u/2 -  viewport_v/2;

        auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // this part of the code makes and formats the file because.
        // opens the file allow it to write it in the correct format
        cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j< image_height; j++) {
            clog << "\rScanlines remaining: " << (image_height - j) << " "<< flush;
            for (int i = 0; i < image_width; i++){
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + ( j * pixel_delta_v);
                auto ray_direction = pixel_center - camera_center;
                ray r(camera_center, ray_direction);

                color pixel_color = ray_color(r);
                write_color(cout, pixel_color);
            }

        }
        clog << "\rDone.                  \n";

}
