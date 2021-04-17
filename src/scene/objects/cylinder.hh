#pragma once

#include "object.hh"

#include <cstdlib>

class Cylinder : public Object
{
public:
    Cylinder(const Point3<>& begin,
            const Point3<>& end,
            const double& radius,
            const std::shared_ptr<TextureMaterial>& material)
        : Object(material), begin_(begin), end_(end), radius_(radius)
    {}

    double getSignedDistance(const Point3<> &fromPoint) override {
        Vector3<> vecToPoint = begin_.vectorTo(fromPoint);
        Vector3<> vecDirector = begin_.vectorTo(end_);

        double t = vecDirector.dot(vecToPoint) / vecDirector.dot(vecDirector);

        Point3<> center = begin_ + vecDirector * t;
        double distance = fromPoint.distanceTo(center) - radius_;

        // How close to the border we are
        // if equal 0, we are at the border
        auto border = (std::abs(t - 0.5) - 0.5) * vecDirector.norme();

        // Exterior distance from fromPoint to the edge of our cylinder
        auto exteriorDistanceVector = Vector3<>({0,0,0});
        if (distance > 0)
            exteriorDistanceVector[0] = distance;
        if (border > 0)
            exteriorDistanceVector[1] = border;
        auto exteriorDistance = exteriorDistanceVector.norme();

        // Interior distance from fromPoint to the vector director in our cylinder
        auto interiorDistance = std::min(std::max(distance, border), 0.0);

        return exteriorDistance + interiorDistance;
    }

    void translate(const Point3<>& translation) override {
        begin_ += translation;
        end_ += translation;
    }
protected:
    Point3<> begin_;
    Point3<> end_;

    double radius_;
};
