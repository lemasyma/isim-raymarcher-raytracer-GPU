#pragma once

#include <algorithm>

#include "../object.hh"

class Union : public Object {
public:
    Union(std::shared_ptr<Object> firstObject,
                std::shared_ptr<Object> secondObject,
                const std::shared_ptr<TextureMaterial> &material,
                double precision = 2)
    : Object(material), firstObject_(firstObject), secondObject_(secondObject), precision_(precision)
    {}

    double smoothMin(double firstDistance, double secondDistance) {
        // linear interpolation
        double h = std::clamp(((secondDistance - firstDistance)/precision_) + 0.5, 0.0, 1.0);
        return h * firstDistance + (1 - h) * secondDistance - h * (1 - h) * precision_ * 0.5;
    }

    double getSignedDistance(const Point3<>& fromPoint) override {
        return smoothMin(firstObject_->getSignedDistance(fromPoint), secondObject_->getSignedDistance(fromPoint));
    }

    Texture getTexture(const Point3<>& pos) override
    {
        auto firstDistance = firstObject_->getSignedDistance(pos);
        auto secondDistance = secondObject_->getSignedDistance(pos);
        if (firstDistance < secondDistance)
            return firstObject_->getTexture(pos);
        return secondObject_->getTexture(pos);
    }

    // Smooth min but for color
    ColorRGB mixColor(const Point3<>& pos) {
        double h = std::clamp(((secondObject_->getSignedDistance(pos) - firstObject_->getSignedDistance(pos)) / precision_) + 0.5, 0.0, 1.0);
        auto firstColor = firstObject_->getColor(pos);
        auto secondColor = secondObject_->getColor(pos);
        return ColorRGB({firstColor.r_get() * h + (1 - h) * secondColor.r_get(),
                         firstColor.g_get() * h + (1 - h) * secondColor.g_get(),
                         firstColor.b_get() * h + (1 - h) * secondColor.b_get(),
                         });
    }

    ColorRGB getColor(const Point3<>& pos) override
    {
        return mixColor(pos);
    }

    std::shared_ptr<Object> getFirstObject() const {
        return firstObject_;
    }

    std::shared_ptr<Object> getSecondObject() const {
        return secondObject_;
    }

protected:
    std::shared_ptr<Object> firstObject_;
    std::shared_ptr<Object> secondObject_;

    double precision_;
};