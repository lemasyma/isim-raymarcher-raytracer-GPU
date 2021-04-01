#pragma once

#include <cmath>
#include <vector>
#include <thread>
#include "scene.hh"
#include "../types/vector-types.hh"
#include "../types/point-types.hh"
#include "../types/image.hh"

#include "pointIntensityComputer.hh"

class Camera {
public:
    using obj_intersect_t = std::pair<Ray, Scene::object_t>;
    using light_intersect_t = std::pair<Point3<>, Scene::light_t>;

    Camera(const Point3<> &position, const Point3<> &lookPoint, const Vector3<> &up,
           double vertAngle, double horizAngle, double distImage);

    std::vector<Vector3<>> getViewVectors(unsigned rows, unsigned cols) const;

    ColorRGB getRayResult(const Point3<> &pos, const Vector3<> &dir, const Scene &scene) const;

    Image &generateImage(Image &image, const Scene &scene, unsigned threads) const;
    Image &generateImage(Image &image, const Scene &scene) const {
        return generateImage(image, scene, std::max(std::thread::hardware_concurrency() - 1, 0U));
    }

    const Point3<>& getPosition() const
    { return position_; }

    Camera& translate(const Point3<> &translation) { position_ += translation; return *this; }

protected:
    Point3<> position_;
    Point3<> lookPoint_;
    Vector3<> up_;

    double vertAngle_;
    double horizAngle_;

    double distImage_;
};