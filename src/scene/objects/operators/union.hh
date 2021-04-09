#pragma once

#include <algorithm>

#include "../object.hh"

class Union : public Object {
public:
    Union(std::shared_ptr<Object> firstObject,
                std::shared_ptr<Object> secondObject,
                const std::shared_ptr<TextureMaterial> &material)
    : Object(material), firstObject_(firstObject), secondObject_(secondObject)
    {}

    double smoothMin(double firstDistance, double secondDistance, double precision) {
        // linear interpolation
        double h = std::clamp(((secondDistance - firstDistance)/precision) + 0.5, 0.0, 1.0);
        return h * firstDistance + (1 - h) * secondDistance - h * (1 - h) * precision * 0.5;
    }

    double getSignedDistance(const Point3<>& fromPoint) override {
        return smoothMin(firstObject_->getSignedDistance(fromPoint), secondObject_->getSignedDistance(fromPoint), 0.2);
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
};