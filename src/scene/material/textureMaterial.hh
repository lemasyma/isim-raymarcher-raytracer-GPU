#pragma once

#include <vector>
#include "scene/material/texture.hh"
#include "types/vector-types.hh"
#include "types/point-types.hh"
#include "types/colorRGB.hh"

class TextureMaterial
{
public:
    virtual std::shared_ptr<TextureMaterial> clone() const = 0;
    virtual Texture getTexture(const Point3<>& pos) = 0;
    virtual ColorRGB getColor(const Point3<>& pos) const = 0;
};