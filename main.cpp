#include "rtpproject.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "presets.h"
#include "bvh.h"

int main(int argc, char* argv[]) {
        render_many_balls_moving(400, 50, (char*)"test1.ppm");

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

