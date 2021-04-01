#pragma once

#include <cstddef>
#include <vector>
#include <fstream>
#include "colorRGB.hh"

class Image
{
public:
    using size_type = std::size_t;

    Image(const size_type& width, const size_type& height)
        : width_(width), height_(height), data_()
    {
        data_.reserve(width * height);
    }

    ColorRGB& at(const size_type& row, const size_type col)
    {
        size_type index = row * width_ + col;
        return data_[index];
    }

    void saveImage(const std::string& filename)
    {
        std::ofstream output;
        output.open(filename, std::ofstream::trunc);
        output << "P3" << '\n' << width_ << '\n' << height_<< '\n' << "255" << '\n';

        for (auto j = 0U; j < height_; ++j) {
            for (auto i = 0U; i < width_; ++i) {
                output << std::to_string(at(j, i).r_get()) << ' '
                        << std::to_string(at(j, i).g_get()) << ' '
                        << std::to_string(at(j, i).b_get()) << ' ';
                if (i < width_ - 1)
                    output << '\t';
            }
            output << '\n';
        }

        output.close();
    }

    const std::vector<ColorRGB>& data_get() const { return data_; }

public:
    size_type width_;
    size_type height_;
protected:
    std::vector<ColorRGB> data_;
};
