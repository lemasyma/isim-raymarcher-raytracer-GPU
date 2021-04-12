#pragma once

#include "object.hh"

class Plane : public Object {
public:
    Plane(const Vector3<>& director, const Point3<>& inPlane, const std::shared_ptr<TextureMaterial>& material)
            : Object(material), inPlane_(inPlane), director_(director.normalize())
    {}

    double getSignedDistance(const Point3<> &fromPoint) override {
        return director_.dot(Vector3<>({fromPoint[0] - inPlane_[0],
                                        fromPoint[1] - inPlane_[1],
                                        fromPoint[2] - inPlane_[2]}));
    }

protected:
    Vector3<> director_;
    Point3<> inPlane_;
};
