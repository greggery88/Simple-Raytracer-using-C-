#include "rtpproject.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "presets.h"
#include "bvh.h"

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

int main(int argc, char* argv[]) {
        // test_if_ray_is_hitting_anything();


        camera cam;
        hittable_list world;

        cam.aspect_ratio      = 16.0 / 9.0;
        cam.image_width       = 400;
        cam.samples_per_pixel = 500;
        cam.max_depth         = 50;

        char* filename = (char*)"test1"
                                "qqq.ppm";



        render_many_balls_moving(cam, world, filename);












        // if (argc > 1) {
        //         if (strcmp("many_balls500", argv[1]) == 0) {
        //                 // if (argv[i] == "") {
        //                 render_many_balls(1200, 500, (char*) "many_balls500.ppm");
        //                 // } else if (argv[i] == "render_spheres")
        //         }
        //         else if (strcmp("render_many_balls10", argv[1]) == 0) {
        //                         // if (argv[i] == "") {
        //                 render_many_balls(1200, 10, (char*) "many_balls10.ppm");
        //                         // } else if (
        //         }
        //         else if (strcmp("blackhole", argv[1]) == 0) {
        //                 render_black_hole(400, 10, 3, 0.1, (char*) "blackhole");
        //         }
        // }
}

