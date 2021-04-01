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

    virtual std::vector<Point3<>> getIntersect(const Ray& ray) = 0; // FIXME / TODO: define rayon

    virtual double getSignedDistance(const Point3<>& fromPoint) = 0;

    virtual Vector3<> getNormale(const Point3<>& pos) = 0;
    virtual Texture getTexture(const Point3<>& pos) = 0;
    virtual ColorRGB getColor(const Point3<>& pos) = 0;

protected:
    std::shared_ptr<TextureMaterial> material_;
};