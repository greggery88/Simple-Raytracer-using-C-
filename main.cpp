#include "rtpproject.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "bvh.h"
#include "quad.h"

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

    for (int a = -5; a < 5; a++) {
        for (int b = -5; b < 5; b++) {
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
    auto material2 = make_shared<dielectric>(1.4);
    auto material3 = make_shared<dielectric>(1.3);
    auto material4 = make_shared<dielectric>(1.2);
    auto material5 = make_shared<dielectric>(1.1);
    auto material6 = make_shared<dielectric>(1.0);
    auto material7 = make_shared<dielectric>(0.9);

    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));
    world.add(make_shared<sphere>(point3(0, 1, 0), 0.9, material1));
    world.add(make_shared<sphere>(point3(0, 1, 0), 0.8, material2));
    world.add(make_shared<sphere>(point3(0, 1, 0), 0.7, material2));
    world.add(make_shared<sphere>(point3(0, 1, 0), 0.6, material2));
    world.add(make_shared<sphere>(point3(0, 1, 0), 0.5, material2));
    world.add(make_shared<sphere>(point3(0, 1, 0), 0.4, material2));




    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, earth_surface));

    auto materialb = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, materialb));



    // set up the camera positioning and focus
    cam.vfov     = 20;
    cam.lookfrom = point3(-13,8,6);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.1;
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

void quads(camera cam, hittable_list world, char* filename) {


    // Materials
    auto left_red     = make_shared<lambertian>(color(1.0, 0.2, 0.2));
    auto back_green   = make_shared<lambertian>(color(0.2, 1.0, 0.2));
    auto right_blue   = make_shared<lambertian>(color(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<lambertian>(color(1.0, 0.5, 0.0));
    auto lower_teal   = make_shared<lambertian>(color(0.2, 0.8, 0.8));

    // Quads
    world.add(make_shared<Quad>(point3(-3,-2, 5), vec3(0, 0,-4), vec3(0, 4, 0), left_red));
    world.add(make_shared<Quad>(point3(-2,-2, 0), vec3(4, 0, 0), vec3(0, 4, 0), back_green));
    world.add(make_shared<Quad>(point3( 3,-2, 1), vec3(0, 0, 4), vec3(0, 4, 0), right_blue));
    world.add(make_shared<Quad>(point3(-2, 3, 1), vec3(4, 0, 0), vec3(0, 0, 4), upper_orange));
    world.add(make_shared<Quad>(point3(-2,-3, 5), vec3(4, 0, 0), vec3(0, 0,-4), lower_teal));




    cam.vfov     = 80;
    cam.lookfrom = point3(0,0,9);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    render_it(cam, world, filename);
}

void cube(camera cam, hittable_list world, char* filename) {
    double side_length = 10;
    point3 v1 = point3(0, 0, 0);

    vec3 v2 = vec3(side_length, 0, 0);
    vec3 v3 = vec3(0,-side_length,0);
    vec3 v4 = vec3(0,0,side_length);

    auto left_red     = make_shared<lambertian>(color(1.0, 0.2, 0.2));
    auto back_green   = make_shared<lambertian>(color(0.2, 1.0, 0.2));
    auto right_blue   = make_shared<lambertian>(color(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<lambertian>(color(1.0, 0.5, 0.0));
    auto lower_teal   = make_shared<lambertian>(color(0.2, 0.8, 0.8));

    world.add(make_shared<Quad>(v1, v2, v3, left_red));
    world.add(make_shared<Quad>(v1, v3, v4, back_green));
    world.add(make_shared<Quad>(v1, v4, v2, right_blue));


    cam.vfov     = 80;
    cam.lookfrom = point3(-6,4,-5);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    render_it(cam, world, filename);
}

void cornell_box(camera cam, hittable_list world, char* filename) {
    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    world.add(make_shared<Quad>(point3(555,0,0), vec3(0,555,0), vec3(0,0,555), green));
    world.add(make_shared<Quad>(point3(0,0,0), vec3(0,555,0), vec3(0,0,555), red));
    world.add(make_shared<Quad>(point3(113, 554, 127), vec3(330,0,0), vec3(0,0,305), light));
    world.add(make_shared<Quad>(point3(0,0,0), vec3(555,0,0), vec3(0,0,555), white));
    world.add(make_shared<Quad>(point3(555,555,555), vec3(-555,0,0), vec3(0,0,-555), white));
    world.add(make_shared<Quad>(point3(0,0,555), vec3(555,0,0), vec3(0,555,0), white));


    cam.vfov     = 40;
    cam.lookfrom = point3(278, 278, -800);
    cam.lookat   = point3(278, 278, 0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    render_it(cam, world, filename);
}

void blackhole(camera cam, hittable_list world, char* filename) {
    auto red   = make_shared<lambertian>(color(0.8, 0.8, 0.8));
}

void simpole_light(camera cam, hittable_list world, char* filename) {
    auto earth_texture = make_shared<image_texture>("Earthmap 1024x512.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, earth_surface));
    world.add(make_shared<sphere>(point3(0,2,0), 2, earth_surface));

    auto difflight = make_shared<diffuse_light>(color(4,4,4));
    world.add(make_shared<Quad>(point3(3,1,-2), vec3(2,0,0), vec3(0,2,0), difflight));

    cam.vfov     = 20;
    cam.lookfrom = point3(26,3,6);
    cam.lookat   = point3(0,2,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    render_it(cam, world, filename);
}
int main(int argc, char* argv[]) {
    camera cam;
    hittable_list world;
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 1000;
    cam.max_depth         = 50;
    cam.background        = color(0,0,0);


    char* filename = new char[strlen(argv[1])+strlen((char*)".ppm")+1];
    strcpy(filename, argv[1]);
    strcat(filename, ".ppm");
// char* filename = (char*)"th.ppm";

    // std::clog << filename << "\n";
    switch (7) {
        case 0: test_if_ray_is_hitting_anything(); break;
        case 1: render_many_balls(cam, world, filename); break;
        case 2: render_many_balls_moving(cam,  world, filename); break;
        case 3: render_checkered_sphers(cam, world, filename); break;
        case 4: earth(cam, world, filename); break;
        case 5: quads(cam, world, filename); break;
        case 6: cube(cam, world, filename); break;
        case 7: cornell_box(cam, world, filename); break;
        case 8: blackhole(cam, world, filename); break;
        case 9: simpole_light(cam, world, filename); break;

    }
}

