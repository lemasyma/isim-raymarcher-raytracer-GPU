#pragma once

#include "object.hh"


class Sphere : public Object
{
public:
    Sphere(const Point3<>& center, const double& radius, const std::shared_ptr<TextureMaterial>& material)
        : Object(material), center_(center), radius_(radius)
    {}

    Sphere(const Point3<>& center, const double& radius)
            : Sphere(center, radius, nullptr)
    {}

    std::vector<Point3<>> getIntersect(const Ray& ray) override;

    Vector3<> getNormale(const Point3<>& pos) override
    {
        auto vector = Vector3<>::distancePoints(center_, pos);
        return vector /= vector.norme();
    }

    double getSignedDistance(const Point3<> &fromPoint) override {
        return fromPoint.distanceTo(center_) - radius_;
    }

    Texture getTexture(const Point3<>& pos) override
    { return material_->getTexture(pos); }

    ColorRGB getColor(const Point3<>& pos) override
    { return material_->getColor(pos); }

    const Point3<>& getCenter() const
    { return center_; }

    double getRadius() const
    { return radius_; }

protected:
    Point3<> center_;
    double radius_;
};