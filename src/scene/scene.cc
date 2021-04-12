#include "scene.hh"

std::pair<double, std::shared_ptr<Object>> Scene::getDist(const Point3<> &p) const {
    std::pair<double, std::shared_ptr<Object>> res{std::numeric_limits<double>::infinity(), nullptr};

    for (const auto &object : objects_) {
        double objectDist = object->getSignedDistance(p);
        if (objectDist < res.first) {
            res.first = objectDist;
            res.second = object;
        }
    }

    return res;
}

Vector3<> Scene::computeNormal(const Point3<> &p) const {
    auto dist = getDist(p);
    return Vector3<>({
        dist.first - getDist(p - Point3<>({Scene::normalePrecision, 0, 0})).first,
        dist.first - getDist(p - Point3<>({0, Scene::normalePrecision, 0})).first,
        dist.first - getDist(p - Point3<>({0, 0, Scene::normalePrecision})).first,
    }).normalize();
}
