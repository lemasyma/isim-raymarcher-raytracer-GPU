#pragma once

#include "object.hh"

class Plane : public Object {
public:
    Plane(const Vector3<>& director, const std::shared_ptr<TextureMaterial>& material)
            : Object(material), director_(director.normalize())
    {}

    double getSignedDistance(const Point3<> &fromPoint) override {
        return director_.dot(Vector3<>({fromPoint[0], fromPoint[1], fromPoint[2]}));
    }

protected:
    Vector3<> director_;
};
