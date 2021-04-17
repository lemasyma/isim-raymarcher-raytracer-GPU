#pragma once

#include "object.hh"

class Sphere : public Object
{
public:
    Sphere(const Point3<>& center, const double& radius, const std::shared_ptr<TextureMaterial>& material)
        : Object(material), center_(center), radius_(radius)
    {}

    double getSignedDistance(const Point3<> &fromPoint) override {
        return fromPoint.distanceTo(center_) - radius_;
    }

    void translate(const Point3<>& translation) override {
        center_ += translation;
    }

    const Point3<>& getCenter() const
    { return center_; }

    double getRadius() const
    { return radius_; }

protected:
    Point3<> center_;
    double radius_;
};