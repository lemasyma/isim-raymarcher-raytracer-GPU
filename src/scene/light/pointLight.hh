#pragma once

#include "light.hh"

class PointLight : public Light {

public:
    PointLight(const Point3<> &position)
            : Light(position) {}

    void abstractMethod() override {
        throw std::logic_error("Not implemented");
    }
};