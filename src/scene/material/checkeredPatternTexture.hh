#pragma once

#include <vector>
#include <memory>
#include <cmath>
#include "textureMaterial.hh"
#include "types/colorRGB.hh"

class CheckeredPatternTexture : public TextureMaterial
{
public:
    CheckeredPatternTexture(const Texture& texture,
            const ColorRGB& color1,
            const ColorRGB& color2)
        : texture_(texture), color_1(color1), color_2(color2)
    {}

    std::shared_ptr<TextureMaterial> clone() const override
    { return std::make_shared<CheckeredPatternTexture>(*this); }

    Texture getTexture(const Point3<>&) override
    { return texture_; }

    ColorRGB getColor(const Point3<>& point) const override
    {
        if (((int) round(std::abs(point[0])) % 2 == 0 && (int) round(std::abs(point[2])) % 2 == 0)
        || ((int) round(std::abs(point[0])) % 2 == 1 && (int) round(std::abs(point[2])) % 2 == 1))
            return color_1;
        return color_2;
    }
protected:
    Texture texture_;
    ColorRGB color_1;
    ColorRGB color_2;
};