//
// Created by Jack Williamson on 12/20/24.
//

#ifndef COLOR_H
#define COLOR_H
# include "vec3.h"
#include <iostream>
using color = vec3;

void write_color(std::ostream& out, const color& pixel_color){\

   // define the x, y, z values as R, G, and B so they can be referenced as such.
   auto r = pixel_color.x();
   auto g = pixel_color.y();
   auto b = pixel_color.z();

   // convert the RGB [0,1] components of the color vector to bytes range [0,255] so they can be read in the ppm file
   int rbyte = int(255.999 * r);
   int gbyte = int(255.999 * g);
   int bbyte = int(255.999 * b);

   // write thie output of the color vecter to the stream so it can be drawn in the file.
   out << rbyte << " " << gbyte << " " << bbyte << "\n";
}
#endif //COLOR_H
