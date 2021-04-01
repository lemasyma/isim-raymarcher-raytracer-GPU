#pragma once

#include "scene.hh"
#include "scene/light/light.hh"

#include "../types/colorRGB.hh"

class RayCaster {
public:
    RayCaster(const Scene &scene, const Point3<> &src, const Vector3<> &dir, int reflectionLimit)
        : reflectLimit(reflectionLimit), scene(scene), src(src), dir(dir.normalize()) {}

    Vector3<> getRayIntensity() const;
    ColorRGB getRayColor() const;

    int reflectLimit;
protected:
    const Scene &scene;
    const Point3<> src;
    const Vector3<> dir;
};