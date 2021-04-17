#pragma once

#include "object.hh"

class Torus : public Object
{
public:
    Torus(const Point3<> &center,
            double bigRadius,
          double smallRadius,
          const std::shared_ptr<TextureMaterial>& material)
        : Object(material), center_(center), bigRadius_(bigRadius), smallRadius_(smallRadius)
    {}

    double getSignedDistance(const Point3<> &fromPoint) override {
        Point3<> pointFromOrigin = fromPoint - center_;
        double distanceFromCenter = Vector3<>({pointFromOrigin[0], 0, pointFromOrigin[2]}).norme() - bigRadius_;
        return Vector3<>({distanceFromCenter,pointFromOrigin[1],0}).norme() - smallRadius_;
    }

    void translate(const Point3<>& translation) override {
        center_ += translation;
    }
protected:
    Point3<> center_;

    double bigRadius_;
    double smallRadius_;
};
