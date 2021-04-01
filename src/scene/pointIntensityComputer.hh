#pragma once

#include "scene/light/light.hh"
#include "scene.hh"
#include "rayCaster.hh"

class PointIntensityComputer {
public:
    PointIntensityComputer(const Scene &scene, const Ray &ray, const std::shared_ptr<Object> &object, int relfectionLimit)
        : scene(scene),
          ray(ray),
          object(object),
          reflectLimit(relfectionLimit),
          texture_(object->getTexture(ray.point_)),
          obj_color_floating_(Light::convertColorToFloating(
                  object->getColor(ray.point_))),
          normal_(scene.computeNormal(ray.point_))
    {}

//    bool isPointVisible(const Light& light, const Vector3<> &toLight) const {
//        // Check if the front / back of the face is visible by the light
//        {
//            // If normal and light are in same direction
//            if (normal_.dot(toLight) >= 0) {
//                // If intersection and normal in same direction -> error
//                if (normal_.dot(obj_intersect.first.vector_) > 0)
//                    return {};
//            } else {
//                // If intersection and normal in different direction -> error
//                if (normal_.dot(obj_intersect.first.vector_) < 0)
//                    return {};
//            }
//        }
//
//        for (const auto &object : scene.objects()) {
//            auto objIntersects = object->getIntersect(Ray(obj_intersect.first.point_, toLight));
//            for (const auto& point : objIntersects) {
//                if (isPointBetweenPoints(obj_intersect.first.point_, light.getPosition(), point))
//                    return false;
//            }
//        }
//
//        return true;
//    }

    Vector3<> getPointReflection() const {
        auto reflective = ray.vector_.copy().normalize().reflective(normal_);
        auto offsetStart = ray.point_ + (reflective.copy().normalize() * Scene::intersectPrecision * 4);
        auto rayCaster = RayCaster(scene, offsetStart, reflective, reflectLimit - 1);
        return rayCaster.getRayIntensity() * texture_.ks;
    }

    Vector3<> getPointLightDiffusion(const Vector3<> &lightItensity, double angleFactor) const {
        return obj_color_floating_ * texture_.kd * angleFactor * lightItensity;
    }

    Vector3<> getPointLightSpecular(const Vector3<> &lightItensity, const Vector3<> &toLight) const {
        const auto reflective = ray.vector_.copy().normalize().reflective(normal_);
        const auto reflectiveDot = reflective.dot(toLight);
        if (reflectiveDot < 0)
            return Vector3<>({0, 0, 0});

        return lightItensity * texture_.ks * pow(reflectiveDot, texture_.ns);
    }

    Vector3<> getPointIntensity() const {
        auto res = Vector3<>({0, 0, 0});

        for (const auto& light : scene.lights()) {
            const auto toLight = ray.point_.vectorTo(light->getPosition()).normalize();
//            if (isPointVisible(*light, toLight)) {
                // gather neceassary data
                const auto lightItensity = Light::convertColorToFloating(light->getColor());
                // add diffusion
                res += Light::clampColorFloating(
                        getPointLightDiffusion(lightItensity, normal_.dot(toLight)));
                // add specular
                res += Light::clampColorFloating(
                        getPointLightSpecular(lightItensity, toLight));
//            }
//             add reflection
            if (reflectLimit > 0) {
                res += Light::clampColorFloating(getPointReflection());
            }
        }

        return res;
    }

public:
    const Scene &scene;
    const Ray ray;
    const std::shared_ptr<Object> object;
    int reflectLimit;
private:
    const Texture texture_;
    const Vector3<> obj_color_floating_;
    const Vector3<> normal_;
};