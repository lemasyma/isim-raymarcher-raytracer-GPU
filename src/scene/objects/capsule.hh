#pragma once

#include "object.hh"

class Capsule : public Object
{
public:
    Capsule(const Point3<>& begin,
            const Point3<>& end,
            const double& radius,
            const std::shared_ptr<TextureMaterial>& material)
        : Object(material), begin_(begin), end_(end), radius_(radius)
    {}

    double getSignedDistance(const Point3<> &fromPoint) override {
        Vector3<> vecToPoint = begin_.vectorTo(fromPoint);
        Vector3<> vecDirector = begin_.vectorTo(end_);

        double t = std::clamp((vecDirector.dot(vecToPoint) / vecDirector.dot(vecDirector)), 0.0, 1.0);

        Point3<> center = begin_ + vecDirector * t;

        return fromPoint.distanceTo(center) - radius_;
    }
protected:
    Point3<> begin_;
    Point3<> end_;

    double radius_;
};
