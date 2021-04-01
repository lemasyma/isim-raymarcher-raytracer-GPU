#pragma once

#include <initializer_list>
#include <array>
#include <iostream>
#include <functional>
#include <iterator>
#include <ostream>
#include <string>
#include <type_traits>

template<typename T, unsigned N>
class CoordinateContainer
{
protected:
    template<unsigned M, typename U>
    using if_coord_type = typename std::enable_if<M - 1 < N, U>::type;

    using self_type = CoordinateContainer<T, N>;

public:
    // Ctors
    CoordinateContainer()
        : elts_( {0} )
    {}
    CoordinateContainer(const std::array<T, N>& init)
    { std::copy(init.begin(), init.end(), elts_.begin()); }

    CoordinateContainer(const self_type& copy_from)
    { std::copy(copy_from.begin(), copy_from.end(), elts_.begin()); }

    CoordinateContainer(const self_type&& copy_from)
    { std::copy(copy_from.begin(), copy_from.end(), elts_.begin()); }

    // Dimension conditional getter / setters
    // 1+ : X
    template<class X = T> if_coord_type<1, X>
        x_get() const { return elts_[0]; }
    template<class X = T> if_coord_type<1, self_type&>
        x_set(const T& elt) { elts_[0] = elt; return *this; }
    // 2+ : Y
    template<class X = T> if_coord_type<2, X>
        y_get() const { return elts_[1]; }
    template<class X = T> if_coord_type<2, self_type&>
        y_set(const T& elt) { elts_[1] = elt; return *this; }
    // 3+ : Z
    template<class X = T> if_coord_type<3, X>
        z_get() const { return elts_[2]; }
    template<class X = T> if_coord_type<3, self_type&>
        z_set(const T& elt) { elts_[2] = elt; return *this; }

    // Misc getter
    unsigned dimension_get() const { return N;}
    //
    // Useful array functions
    auto begin() { return elts_.begin(); }
    auto begin() const { return elts_.begin(); }
    auto end() { return elts_.end(); }
    auto end() const { return elts_.end(); }

    auto rbegin() { return elts_.rbegin(); }
    auto rbegin() const { return elts_.rbegin(); }
    auto rend() { return elts_.rend(); }
    auto rend() const { return elts_.rend(); }

    T& at(unsigned index) { return elts_.at(index); }
    T at(unsigned index) const { return elts_.at(index); }
    T&  operator[](unsigned index) { return elts_[index]; }
    T operator[](unsigned index) const { return elts_[index]; }

    std::ostream& print_coordinates(std::ostream& os) const
    {
        os << '{';
        std::copy(this->begin(), this->end() - 1,
                std::ostream_iterator<T>(os, ", "));
        std::copy(this->end() - 1, this->end(),
                std::ostream_iterator<T>(os));
        return os << '}';
    }

protected:
    std::array<T, N> elts_;
};

template<typename T, unsigned N>
std::ostream& operator<<(std::ostream& os,
        const CoordinateContainer<T, N>& coords)
{
    os << "Coordinates" << coords.dimension_get();
    return coords.print_coordinates(os);
}
