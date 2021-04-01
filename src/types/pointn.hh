#pragma once

#include <initializer_list>
#include <array>
#include <iostream>
#include <functional>
#include <ostream>
#include <string>
#include <type_traits>
#include "coordinate-container.hh"

template<typename T, unsigned N>
class VectorN;

template<typename T, unsigned N>
class PointN: public CoordinateContainer<T, N>
{
protected:
    using self_type = PointN<T, N>;
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
    self_type operator*(const U& rhs) const
    { return self_type(*this) *= rhs; }

    template<typename U>
    self_type operator+(const U& rhs) const
    { return self_type(*this) += rhs; }

    template<typename U>
    self_type operator-(const U& rhs) const
    { return self_type(*this) -= rhs; }

    void apply_operator(const T& scalar, bin_op_type func)
    {
        for (T& elt : this->elts_)
            elt = func(elt, scalar);
    }

    void apply_operator(const VectorN<T, N>& vect, bin_op_type func)
    {
        for (auto i = 0U; i < N; ++i)
            (*this)[i] = func((*this)[i], vect[i]);
    }

    void apply_operator(const self_type& rhs, bin_op_type func)
    {
        for (auto i = 0U; i < N; ++i)
            (*this)[i] = func((*this)[i], rhs[i]);
    }
    // endregion

    VectorN<T, N> vectorTo(const PointN& dst) const;

    self_type middlePoint(const self_type& dst) const
    {
        self_type res{};
        for (auto i = 0U; i < N; ++i)
            res[i] = (*this)[i] + ((dst[i] - (*this)[i]) / 2.0);
        return res;
    }

    double distanceTo(const PointN& dst) const
    { return this->vectorTo(dst).norme(); }
};

#include "pointn.hxx"