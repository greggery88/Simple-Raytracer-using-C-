//
// Created by Jack Williamson on 1/1/25.
//

#ifndef PRESETS_H
#define PRESETS_H
#include "bvh.h"
#include "material.h"

inline void render_many_balls( int pixel_width, int samples, char* filename) {
    std::clog << filename <<std::endl;
    camera cam;
    hittable_list world;
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));


    // set up the camera
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = pixel_width;
    cam.samples_per_pixel = samples;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_distance    = 10.0;

    cam.render(world, filename);
}
inline void render_three_balls_on_green(hittable_list world, camera cam, int pixel_width, int samples) {

    auto material_ground = make_shared<lambertian>(color(0.8,0.8,0));
    auto material_center = make_shared<lambertian>(color(0.1,0.3,0.5));
    auto material_bubble = make_shared<dielectric>(1.5);
    auto material_left = make_shared<dielectric>(1.0/1.5);
    auto material_right = make_shared<metal>(color(0.6,0.4,0.2), 0.5);

    world.add(make_shared<sphere>(point3(0.0,-100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0,0.0, -1.2), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0,0.0, -1.0), 0.6, material_right));
    world.add(make_shared<sphere>(point3(1, 0, -1), 0.5, material_bubble));

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = pixel_width;
    cam.samples_per_pixel = samples;
    cam. max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = point3(-2, 2, 1);
    cam.lookat = point3(0, 0, -1);
    cam.vup = point3(0, 1, 0);

    cam.defocus_angle = 10.0;
    cam.focus_distance = 3.4;
}

inline void render_many_balls_moving( int pixel_width, int samples, char* filename) {
    std::clog << filename <<std::endl;

    hittable_list world;
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center +vec3(0,random_double(0,0.5), 0);
                    world.add(make_shared<sphere>(center, center2, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    world = hittable_list(make_shared<bvh_node>(world));

    camera cam;
    // set up the camera
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = pixel_width;
    cam.samples_per_pixel = samples;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_distance    = 10.0;

    cam.render(world, filename);
}


#endif //PRESETS_H
