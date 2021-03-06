#pragma once

#include <iostream>
#include <cstdlib>

#include "object.hh"

class Cube : public Object
{
public:
    Cube(const Point3<> &center,
          const Point3<> &sides,
          const std::shared_ptr<TextureMaterial>& material)
        : Object(material), center_(center), sides_(sides)
    {}

    double getSignedDistance(const Point3<> &fromPoint) override {
        Point3<> pointFromOrigin = fromPoint - center_;
        Vector3<> vectorFromOrigin = sides_.vectorTo(Point3<>({std::abs(pointFromOrigin[0]),
                                                                std::abs(pointFromOrigin[1]),
                                                                 std::abs(pointFromOrigin[2])}));
        for (unsigned i = 0; i < 3; ++i) {
            if (vectorFromOrigin[i] < 0)
                vectorFromOrigin[i] = 0;
        }

        return vectorFromOrigin.norme();
    }
protected:
    Point3<> center_;

    Point3<> sides_; //width, height, depth
};
