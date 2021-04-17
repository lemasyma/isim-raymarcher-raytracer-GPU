#pragma once

#include "object.hh"

class Plane : public Object {
public:
    Plane(const Vector3<>& director, double distance, const std::shared_ptr<TextureMaterial>& material)
            : Object(material), distance_(distance), director_(director.normalize())
    {}

    double getSignedDistance(const Point3<> &fromPoint) override {
        return director_.dot(Vector3<>({fromPoint[0],
                                        fromPoint[1],
                                        fromPoint[2]})) + distance_;
    }

    void translate(const Point3<>& translation) override {
        director_ += Vector3<>({translation[0], translation[1], translation[2]});
        director_.normalize();
    }

protected:
    Vector3<> director_;
    double distance_;
};
