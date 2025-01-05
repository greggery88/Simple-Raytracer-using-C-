//
// Created by Jack Williamson on 1/4/25.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include "color.h"
#include "vec3.h"

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

#endif //TEXTURE_H