#pragma once

#include "vectorn.hh"
#include "point-types.hh"

template<typename T, unsigned N>
std::ostream& operator<<(std::ostream& os, const VectorN<T, N>& vec)
{
    os << "Vector" << vec.dimension_get();
    return vec.print_coordinates(os);
}

template<typename T, unsigned int N>
VectorN<T, N> VectorN<T, N>::distancePoints(const PointN<T, N> &src, const PointN<T, N> &dst) {
    VectorN<T, N> res({ 0 });
    for (auto i = 0U; i < N; ++i)
        res[i] = dst[i] - src[i];
    return res;
}