#pragma once

#include <initializer_list>
#include <array>
#include <iostream>
#include <functional>
#include <ostream>
#include <string>
#include <type_traits>
#include <cmath>
#include "coordinate-container.hh"

template<typename T, unsigned N>
class PointN;

template<typename T, unsigned N>
class VectorN: public CoordinateContainer<T, N>
{
protected:
    using self_type = VectorN<T, N>;
    using bin_op_type = std::function<T(const T&, const T&)>;

public:
    // Inherit ctors
    using CoordinateContainer<T, N>::CoordinateContainer;

    // region Operators
    template<typename U>
    self_type& operator*=(const U& rhs)
    {
        apply_operator(rhs, std::multiplies<T>());
        return *this;
    }

    template<typename U>
    self_type& operator+=(const U& rhs)
    {
        apply_operator(rhs, std::plus<T>());
        return *this;
    }

    template<typename U>
    self_type& operator-=(const U& rhs)
    {
        apply_operator(rhs, std::minus<T>());
        return *this;
    }

    template<typename U>
    self_type& operator/=(const U& rhs)
    {
        apply_operator(rhs, std::divides<T>());
        return *this;
    }

    template<typename U>
    self_type operator*(const U& rhs) const
    { return self_type(*this) *= rhs; }

    template<typename U>
    self_type operator+(const U& rhs) const
    { return self_type(*this) += rhs; }

    template<typename U>
    self_type operator-(const U& rhs) const
    { return self_type(*this) -= rhs; }

    template<typename U>
    self_type operator/(const U& rhs) const
    { return self_type(*this) /= rhs; }

    PointN<T, N>operator+(const PointN<T, N>& rhs) const
    { return  rhs + *this; }

    bool operator==(const VectorN& rhs) const
    { return this->elts_ == rhs.elts_; }

    bool operator!=(const VectorN& rhs) const
    { return this->elts_ != rhs.elts_; }

    void apply_operator(const T& scalar, bin_op_type func)
    {
        for (T& elt : this->elts_)
            elt = func(elt, scalar);
    }

    void apply_operator(const self_type& rhs, bin_op_type func)
    {
        for (auto i = 0U; i < N; ++i)
            (*this)[i] = func((*this)[i], rhs[i]);
    }
    //endregion

    double norme() const {
        double res = 0;
        // replace iter with 0 -> n to use loop unrolling
        for (auto it = this->begin(); it != this->end(); ++it)
            res += (*it) * (*it);
        return sqrt(res);
    }

    VectorN& normalize() {
        auto norm = norme();
        if (norm != 0)
            return (*this) /= norm;
        return *this;
    }

    VectorN normalize() const {
        auto norm = norme();
        if (norm != 0)
            return (*this) / norm;
        return VectorN({0, 0, 0});
    }

    VectorN copy() const {
        return VectorN(*this);
    }

    // FIXME: fix for n dimension
    VectorN cross(const VectorN& rhs) const
    {
        return VectorN({
            (*this)[1] * rhs[2] - (*this)[2] * rhs[1],
            (*this)[2] * rhs[0] - (*this)[0] * rhs[2],
            (*this)[0] * rhs[1] - (*this)[1] * rhs[0]
        });
    }

    double dot(const VectorN& rhs) const
    {
        double sum = 0;
        for (auto i = 0U; i < N; ++i)
            sum += (*this)[i] * rhs[i];
        return sum;
    }

    VectorN reflective(const VectorN& normal) const
    {
        return (*this) - (normal * (2 * this->dot(normal)));
    }

    static VectorN<T, N> distancePoints(const PointN<T, N>& src, const PointN<T, N>& dst);
};

#include "vectorn.hxx"
