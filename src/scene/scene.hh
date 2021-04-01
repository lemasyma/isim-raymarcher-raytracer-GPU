#pragma once

#include <vector>
#include <memory>
#include "scene/objects/object.hh"
#include "scene/light/light.hh"

class Scene {
public:
    constexpr static double intersectPrecision = 0.001;
    constexpr static double normalePrecision = 0.001;

    using self_t = Scene;

    using object_t = std::shared_ptr<Object>;
    using objects_t = std::vector<object_t>;

    using light_t = std::shared_ptr<Light>;
    using lights_t = std::vector<light_t>;

    objects_t &objects() { return objects_; }

    const objects_t &objects() const { return objects_; }

    self_t &addObject(const object_t &object) {
        objects_.push_back(object);
        return *this;
    }

    lights_t &lights() { return lights_; }

    const lights_t &lights() const { return lights_; }

    self_t &addLight(const light_t &light) {
        lights_.push_back(light);
        return *this;
    }

    std::pair<double, std::shared_ptr<Object>> getDist(const Point3<> &p) const;

    Vector3<> computeNormal(const Point3<> &p) const;

protected:
    // objectS
    objects_t objects_;
    // light sourceS
    lights_t lights_;
    // camera
    // FIXME: todo
};
