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

    static Point3<> offsetPoint(const Point3<>& start, const Vector3<> &inDir, const Vector3<> &outDir) {
        return start
               // get closer to real intersection
               + (inDir * Scene::intersectPrecision / 2.0)
               // relaunch with safe distance to avoid self collisionning
               + (outDir * Scene::intersectPrecision * 25.0);
    }

    double shadowingFactor(const Light& light, const Vector3<> &toLight) const {
        // Check if the front / back of the face is visible by the light
        /*
        {
            // If normal and light are in same direction
            if (normal_.dot(toLight) >= 0) {
                // If intersection and normal in same direction -> error
                if (normal_.dot(ray.vector_) > 0)
                    return {};
            } else {
                // If intersection and normal in different direction -> error
                if (normal_.dot(ray.vector_) < 0)
                    return {};
            }
        }
        */

        double minDistSeen = std::numeric_limits<double>::infinity();
        double totDistance = 0.0;
        auto finalObject = std::shared_ptr<Object>();

        auto offsetOrigin = offsetPoint(ray.point_, ray.vector_, toLight);
        double maxDist = offsetOrigin.distanceTo(light.getPosition()) + Scene::intersectPrecision * 100;

        for (auto i = 0U; i < 150; ++i) {
            auto nextPoint = offsetOrigin + (toLight * totDistance);

            // Update total distance
            auto dist = scene.getDist(nextPoint);
            totDistance += dist.first;

            // save minimal distance encountered
            if (dist.first < minDistSeen && dist.second != object)
                minDistSeen = dist.first;

            // if very close (threshold), HIT
            if (dist.first < Scene::intersectPrecision) {
                finalObject = dist.second;
                break;
            }
            // if further than light, we didnt found object
            if (totDistance > maxDist)
                break;
        }

        if (finalObject)
            return 0.0;

        constexpr double softShadowLimit = Scene::intersectPrecision * 75;
        if (minDistSeen < softShadowLimit)
            return minDistSeen / softShadowLimit;

        return 1.0;
    }

    Vector3<> getPointReflection() const {
        auto reflective = ray.vector_.copy().normalize().reflective(normal_);
        auto offsetStart = offsetPoint(ray.point_, ray.vector_, reflective.copy().normalize());
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
            // gather neceassary data
            const auto toLight = ray.point_.vectorTo(light->getPosition()).normalize();
            const auto lightItensity = Light::convertColorToFloating(light->getColor());
            double shadowFactor = shadowingFactor(*light, toLight);

            auto diffuseLight = Light::clampColorFloating(
                    getPointLightDiffusion(lightItensity, normal_.dot(toLight)));

            if (shadowFactor > 0.1) {
                // add diffusion
                res += (diffuseLight * shadowFactor);
                // add specular
                res += Light::clampColorFloating(
                        getPointLightSpecular(lightItensity, toLight));
            } else {
                res += diffuseLight * 0.1;
            }
            // add reflection
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