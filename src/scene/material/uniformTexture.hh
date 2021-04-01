#pragma once

#include <vector>
#include "textureMaterial.hh"
#include "types/colorRGB.hh"

class UniformTexture : public TextureMaterial
{
public:
    UniformTexture(const Texture& texture, const ColorRGB& color)
        : texture_(texture), color_(color)
    {}

    std::shared_ptr<TextureMaterial> clone() const override
    { return std::make_shared<UniformTexture>(*this); }

    Texture getTexture(const Point3<>&) override
    { return texture_; }

    ColorRGB getColor(const Point3<>&) const override
    { return color_; }
protected:
    Texture texture_;
    ColorRGB color_;
};