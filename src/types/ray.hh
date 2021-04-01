#pragma once

#include "vector-types.hh"
#include "point-types.hh"

class Ray
{
public:
    Ray(const Point3<>& point, const Vector3<>& vector)
        : point_(point), vector_(vector)
    {}

public:
    Point3<> point_;
    Vector3<> vector_;
};