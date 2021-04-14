#pragma once

#include <algorithm>

#include "../object.hh"

class Subtraction : public Object {
public:
    Subtraction(std::shared_ptr<Object> firstObject,
                std::shared_ptr<Object> secondObject,
                const std::shared_ptr<TextureMaterial> &material)
    : Object(material), firstObject_(firstObject), secondObject_(secondObject)
    {}

    double getSignedDistance(const Point3<>& fromPoint) override {
        return std::max(-firstObject_->getSignedDistance(fromPoint), secondObject_->getSignedDistance(fromPoint));
    }

    ColorRGB getColor(const Point3<>& pos) override
    {
        if (-firstObject_->getSignedDistance(pos) > secondObject_->getSignedDistance(pos))
            return firstObject_->getColor(pos);
        return secondObject_->getColor(pos);
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