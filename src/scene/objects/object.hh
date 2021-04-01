#pragma once

#include <vector>
#include <memory>
#include "scene/material/textureMaterial.hh"
#include "types/vector-types.hh"
#include "types/ray.hh"

class Object
{
public:
    explicit Object(const std::shared_ptr<TextureMaterial>& material)
        : material_(material)
    {}

    virtual double getSignedDistance(const Point3<>& fromPoint) = 0;

    virtual Texture getTexture(const Point3<>& pos)
    { return material_->getTexture(pos); }

    virtual ColorRGB getColor(const Point3<>& pos)
    { return material_->getColor(pos); }


protected:
    std::shared_ptr<TextureMaterial> material_;
};