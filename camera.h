//
// Created by Jack Williamson on 12/22/24.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <fstream>

#include "hittable.h"
#include "material.h"

class camera {
    public:
        // set up the image.
        double aspect_ratio = 1.0;
        int image_width = 100;
        int samples_per_pixel = 10;
        int max_depth = 10;

        double vfov = 90;
        point3 lookfrom = point3(0, 0, 0);
        point3 lookat = point3(0, 0, -1);
        vec3 vup = vec3(0, 1, 0);

        double defocus_angle = 0; //variations anlge of rays through pixel
        double focus_distance = 10; // distance from camera lookfrom point of perfect focus


        void render(const hittable& world, char* file_name) {
            initialize();
            std::ofstream outputFile(file_name);

            if (outputFile.is_open()) {

                outputFile << "P3\n" << image_width << " " << image_height << "\n255\n";

                // goes down
                for (int j = 0; j< image_height; j++) {
                    std::clog << "\rScanlines remaining: " << (image_height - j) << " "<<std::flush;
                    for (int i = 0; i < image_width; i++){
                        color pixel_color(0,0,0);
                        for (int sample = 0; sample < samples_per_pixel; sample++) {
                            ray r = get_ray(i,j);
                            pixel_color += ray_color(r, max_depth ,world);
                        }
                        write_color(outputFile, sample_pixel_scale*pixel_color);
                    }

                }
                std::clog << "\rDone.                  \n";
            }
        }

    private:
        int image_height;          // Render image height
        double sample_pixel_scale; // color scale factor for a sum of pixel samples
        point3 center;             // Camera center
        point3 pixel00_loc;        // locations of pixel 0, 0
        vec3 pixel_delta_u;        // Offset to pixel to teh right.
        vec3 pixel_delta_v;        // Offset to pixel below
        vec3 u, v, w;              // camera frame basics vecters
        vec3 defocus_disk_u;       // horisonatl radius fo dist
        vec3 defocus_disk_v;       // vertical radius of disk




    void initialize() {
        // Make and check imagee height is valid
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        sample_pixel_scale = 1.0/ samples_per_pixel;

        center = lookfrom;

        // Determine viewport dimensions
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2.0 * h * focus_distance;
        auto viewport_width = viewport_height * double(image_width)/image_height;

        // Calculate the u,v,w unit basis vecvtors for the camera coordinates frame.
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = unit_vector(cross(w, u));
        // Calculate the vectors across the horizontal and down the verticle viewport edges.
        auto viewport_u = viewport_width * u;   // vector across viewport horezontral edge
        auto viewport_v = viewport_height * -v; // vector down viewport vertical edge.

        // Calculate the delta vectors
        pixel_delta_u = viewport_u/ image_width;
        pixel_delta_v = viewport_v/ image_height;

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        auto viewport_upper_left =
                    center - (focus_distance * w) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u + pixel_delta_v);

        // Calculate the camera defocus disk basis vectors.
        auto defocus_radius = focus_distance * tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u*defocus_radius;
        defocus_disk_v = v*defocus_radius;
    }

    ray get_ray(int i, int j) const {
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                + ((i + offset.x())*pixel_delta_u)
                + ((j + offset.y())*pixel_delta_v);

        auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // returns the vector to a random point
        return vec3(random_double()-0.5, random_double() -0.5, 0);
    }

    point3 defocus_disk_sample() const {
        // return random point in the camera defocus disk
        auto p = random_in_unit_disk();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }


    color ray_color(const ray& r, int depth, const hittable& world) const {
        if (depth <= 0) return color(0,0,0);

        hit_record rec;
        if (world.hit(r,interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r,rec,attenuation,scattered)) {
                return attenuation * ray_color(scattered,depth-1,world);
            };


            return color(0,0,0);

        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.4,0.7,1.0);
    }
};
#endif //CAMERA_H./
