//
// Created by Jack Williamson on 1/4/25.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include "color.h"
#include "vec3.h"
#include "rpp_stb_image.h"

class Texture {
    public:
    virtual ~Texture() = default;

    virtual color value(double u, double v, const point3& p) const = 0;

};

class solid_color : public Texture {
    public:
    solid_color(const color& albedo) : albedo(albedo) {}

    solid_color(double red, double green, double blue)
                    : solid_color(color(red, green, blue)) {}

    color value(double u, double v, const point3& p) const override {
        return albedo;
    }
    private:
    color albedo;
};

class checker_texture : public Texture {
    public:
    checker_texture(double scale, shared_ptr<Texture> even, shared_ptr<Texture>  odd)
        : inv_scale(1.0/scale), even(even), odd(odd) {}

    checker_texture(double scale, const color& c1, const color& c2)
        :checker_texture(scale, make_shared<solid_color>(c1), make_shared<solid_color>(c2)) {}

    color value(double u, double v, const point3& p) const override {
        auto xInterger = int(std::floor(inv_scale * p.x()));
        auto yInterger = int(std::floor(inv_scale * p.y()));
        auto zInterger = int(std::floor(inv_scale * p.z()));

        bool isEven = (xInterger + yInterger + zInterger) % 2 == 0;

        return isEven ? even->value(u, v, p) : odd->value(u, v, p);
    }
    private:
    double inv_scale;
    shared_ptr<Texture> even, odd;
};

class image_texture : public Texture {
    public:
    image_texture(const char* filename) : image(filename){}

    color value(double u, double v, const point3& p) const override {
        // if we have no texture, then return solid cyan sa a debugging aid.
        if (image.height() <= 0) return color(0, 1, 1);

        // clamp input texture coorindates to [0,1]x[1,0]
        u = interval(0,1).clamp(u);
        v= 1.0 - interval(0,1).clamp(v);

        auto i = int(u* image.width());
        auto j = int (v* image.height());
        auto pixel = image.pixel_data(i, j);

        auto color_scale = 1.0 / 255.0;
        return color(color_scale*pixel[0], color_scale*pixel[1], color_scale*pixel[2]);


    }

private:
    rtw_image image;
};


#endif //TEXTURE_H
