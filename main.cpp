#include "rtpproject.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "presets.h"
#include "bvh.h"


void render_it(camera cam, hittable_list world, char* filename) {
    std::clog << filename <<std::endl;
    world = hittable_list(make_shared<bvh_node>(world));
    cam.render(world, filename);
}


void render_many_balls(camera cam, hittable_list world, char* filename) {

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

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_distance    = 10.0;

    render_it(cam, world, filename);
}
void render_three_balls_on_green(camera cam, hittable_list world, char* filename) {

    auto material_ground = make_shared<lambertian>(color(0.8,0.8,0));
    auto material_center = make_shared<lambertian>(color(0.1,0.3,0.5));
    auto material_bubble = make_shared<dielectric>(1.5);
    auto material_left = make_shared<dielectric>(1.0/1.5);
    auto material_right = make_shared<metal>(color(0.6,0.4,0.2), 0.0);

    world.add(make_shared<sphere>(point3(0.0,-100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0,0.0, -1.2), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0,0.0, -1.0), 0.6, material_right));
    world.add(make_shared<sphere>(point3(1, 0, -1), 0.5, material_bubble));

    cam.vfov = 20;
    cam.lookfrom = point3(-20, 20, 0);
    cam.lookat = point3(0, 0, 0);
    cam.vup = point3(0, 1, 0);

    cam.defocus_angle = 0.03;
    cam.focus_distance = 3.4;

    render_it(cam, world, filename);
}
void render_many_balls_moving(camera cam, hittable_list world, char* filename) {

    auto checker = make_shared<checker_texture>(0.32, color(.2,.3,.1), color(.9,.9,.9));
    auto ground_material = make_shared<lambertian>(checker);
    auto earth_texture = make_shared<image_texture>("Earthmap 1024x512.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);

    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.2) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center +vec3(0,random_double(0,0.5), 0);
                    world.add(make_shared<sphere>(center, center2, 0.2, sphere_material));
                } else if (choose_mat < 0.9) {
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
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, earth_surface));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));



    // set up the camera positioning and focus
    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_distance    = 10.0;

    render_it(cam, world, filename);
}
void test_if_ray_is_hitting_anything() {

        auto material_right = make_shared<metal>(color(0.6,0.4,0.2), 0.5);

        hittable_list world;

        world.add(make_shared<sphere>(point3(0.0,0.0, -1.0), 0.6, material_right));

        world = hittable_list(make_shared<bvh_node>(world));

        ray r = ray(point3(0,0,0), vec3(.001, 0.0001, -1));

        hit_record rec;
        if (world.hit(r,interval(0.001, infinity), rec))
                std::clog << "rays susesfully hitting" << std::endl;
}
void render_checkered_sphers(camera cam, hittable_list world, char* filename) {
    auto checker = make_shared<checker_texture>(0.32, color(.2,.3,.1), color(.9,.9,.9));

    world.add(make_shared<sphere>(point3(0,-10, 0), 10, make_shared<lambertian>(checker)));
    world.add(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;
    render_it(cam, world, filename);
}
void earth(camera cam, hittable_list world, char* filename) {

    auto earth_texture = make_shared<image_texture>("Earthmap 1024x512.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    world.add( make_shared<sphere>(point3(0,0,0), 2, earth_surface));

    cam.vfov     = 20;
    cam.lookfrom = point3(0,0,12);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    render_it(cam, world, filename);
}


int main(int argc, char* argv[]) {
    camera cam;
    hittable_list world;
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1200;
    cam.samples_per_pixel = 500;
    cam.max_depth         = 50;



char* filename = (char*)"earth.ppm";

    // std::clog << filename << "\n";
    switch (2) {
        case 0: test_if_ray_is_hitting_anything(); break;

        case 1: render_many_balls(cam, world, filename); break;

        case 2: render_many_balls_moving(cam,  world, filename); break;

        case 3: render_checkered_sphers(cam, world, filename); break;
        case 4: earth(cam, world, filename); break;

    }
}

