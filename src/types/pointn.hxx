#pragma once

#include "pointn.hh"
#include "vector-types.hh"

template<typename T, unsigned N>
std::ostream& operator<<(std::ostream& os, const PointN<T, N>& vec)
{
    os << "Point" << vec.dimension_get();
    return vec.print_coordinates(os);
}

template<typename T, unsigned N>
VectorN<T, N> PointN<T, N>::vectorTo(const PointN &dst) const
{
    return VectorN<T, N>::distancePoints(*this, dst);
}
