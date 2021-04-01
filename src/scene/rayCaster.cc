#include "rayCaster.hh"
#include "pointIntensityComputer.hh"

Vector3<> RayCaster::getRayIntensity() const {
    double totDistance = 0.0;
    auto finalObject = std::shared_ptr<Object>();


    for (auto i = 0U; i < 20; ++i) {
        auto nextPoint = src + (dir * totDistance);

        auto dist = scene.getDist(nextPoint);
        totDistance += dist.first;

        if (dist.first < Scene::intersectPrecision) {
            finalObject = dist.second;
            break;
        }
        if (totDistance > 20000.0)
            break;
    }

    auto color = ColorRGB(0, 0, 0);
    if (finalObject) {
        auto intersectPoint = src + (dir * totDistance);
        auto computer = PointIntensityComputer(scene, Ray(intersectPoint, dir), finalObject, reflectLimit);
        return computer.getPointIntensity();
    }

    return Light::convertColorToFloating(color);
}

ColorRGB RayCaster::getRayColor() const {
    return Light::convertColorToInteger(getRayIntensity());
}