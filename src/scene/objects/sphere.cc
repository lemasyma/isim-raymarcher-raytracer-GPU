#include "scene/objects/object.hh"
#include "scene/objects/sphere.hh"

std::vector<Point3<>> Sphere::getIntersect(const Ray& ray)
{
    const auto& dir = ray.vector_;
    auto pt0 = ray.point_ - center_;

    // Coefficients du polynôme
    auto a = pow(dir.x_get(), 2) + pow(dir.y_get(), 2) + pow(dir.z_get(), 2);
    auto b = 2 * ( dir.x_get() * pt0.x_get() + dir.y_get() * pt0.y_get() + dir.z_get() * pt0.z_get());
    auto c = pow(pt0.x_get(), 2) + pow(pt0.y_get(), 2) + pow(pt0.z_get(), 2) - pow(radius_, 2);

    // Determinant
    auto delta = pow(b, 2) - (4 * a * c);

    auto res = std::vector<Point3<>>();
    if (delta == 0) {
        auto r = - b / (2 * a);
        res.emplace_back(dir * r + ray.point_);
    } else if (delta > 0) {
        auto r1 = (- b + sqrt(delta)) / (2 * a);
        auto r2 = (- b - sqrt(delta)) / (2 * a);
        res.emplace_back(dir * r1 + ray.point_);
        res.emplace_back(dir * r2 + ray.point_);
    }
    return res;
}