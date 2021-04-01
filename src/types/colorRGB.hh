#pragma once

#include <array>
#include <iostream>

class ColorRGB
{
public:
    using rgb_type = unsigned char;
    using self_type = ColorRGB;
    ColorRGB(const rgb_type& r, const rgb_type& g, const rgb_type& b)
        : rgbs_({ r, g, b })
    {}

    rgb_type& r_get() { return rgbs_[0]; }
    rgb_type r_get() const { return rgbs_[0]; }
    self_type r_set(const rgb_type& r) { rgbs_[0] = r; return *this; }

    rgb_type& g_get() { return rgbs_[1]; }
    rgb_type g_get() const { return rgbs_[1]; }
    self_type g_set(const rgb_type& g) { rgbs_[1] = g; return *this; }

    rgb_type& b_get() { return rgbs_[2]; }
    rgb_type b_get() const { return rgbs_[2]; }
    self_type b_set(const rgb_type& b) { rgbs_[2] = b; return *this; }

    std::array<rgb_type, 3> rgbs_;
};

inline std::ostream& operator<<(std::ostream& os, const ColorRGB& color)
{
    os << "Color(RGB){" << static_cast<int>(color.r_get())
        << ", " << static_cast<int>(color.g_get())
        << ", " << static_cast<int>(color.b_get())
        << "}";
    return os;
}