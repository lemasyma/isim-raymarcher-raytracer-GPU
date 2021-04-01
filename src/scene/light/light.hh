#pragma once

#include <cmath>
#include <algorithm>
#include "types/vector-types.hh"

class Light {
public:

    Light(const Point3<> &position)
            : position_(position) {}

    virtual void abstractMethod() = 0;

    const Point3<> &getPosition() const { return position_; }
    Point3<> &getPosition() { return position_; }

    const ColorRGB &getColor() const { return defaultColor_; }
    ColorRGB &getColor() { return defaultColor_; }

    static Vector3<> convertColorToFloating(const ColorRGB &color) {
        return Vector3<>({
            color.r_get() / 255.0,
            color.g_get() / 255.0,
            color.b_get() / 255.0
        });
    }

    static Vector3<> clampColorFloating(const Vector3<> &color) {
        return Vector3<>({
            std::clamp(color.x_get(), 0.0, 1.0),
            std::clamp(color.y_get(), 0.0, 1.0),
            std::clamp(color.z_get(), 0.0, 1.0)
         });
    }

    static ColorRGB convertColorToInteger(const Vector3<> &color) {
        return {
            static_cast<unsigned char>(std::clamp(round(color.x_get() * 255.0), 0.0, 255.0)),
            static_cast<unsigned char>(std::clamp(round(color.y_get() * 255.0), 0.0, 255.0)),
            static_cast<unsigned char>(std::clamp(round(color.z_get() * 255.0), 0.0, 255.0))
        };
    }

protected:
    Point3<> position_;
    ColorRGB defaultColor_ = ColorRGB(255, 255, 255);
};