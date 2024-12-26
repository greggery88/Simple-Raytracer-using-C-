//
// Created by Jack Williamson on 12/20/24.
//

#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

using color = vec3;

inline double linear_to_gamma(double linear_component) {
   if (linear_component > 0.0)
      return std::sqrt(linear_component);
   return 0;
}

void write_color(std::ostream& out, const color& pixel_color){

   // define the x, y, z values as R, G, and B so they can be referenced as such.
   auto r = pixel_color.x();
   auto g = pixel_color.y();
   auto b = pixel_color.z();

   //Apply linear to gamma transform
   r= linear_to_gamma(r);
   g= linear_to_gamma(g);
   b= linear_to_gamma(b);

   // convert the RGB [0,1] components of the color vector to bytes range [0,255] so they can be read in the ppm file
   static const interval intensity(0.000,0.999);
   int rbyte = int(255.999 * intensity.clamp(r));
   int gbyte = int(255.999 * intensity.clamp(g));
   int bbyte = int(255.999 * intensity.clamp(b));

   // write thie output of the color vecter to the stream so it can be drawn in the file.
   out << rbyte << " " << gbyte << " " << bbyte << "\n";
}
#endif //COLOR_H
