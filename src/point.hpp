#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

template <std::size_t dimension, typename PointType> class Point
{
private:
    std::size_t size() const { return dimension; }

public:
    std::array<PointType, dimension> values;

    Point() = default;
    //    Point(PointType x, PointType y) : values { x, y } {}
    //    Point(PointType x, PointType y, PointType z) : values { x, y, z } { static_assert(dimension > 2); }
    template <typename... Args>
    Point(PointType pt, Args&&... args) : values { pt, static_cast<PointType>(std::forward<Args>(args))... }
    {
        static_assert(sizeof...(args) + 1 == dimension);
    }
    PointType& x() { return values[0]; }
    PointType x() const { return values[0]; }

    PointType& y()
    {
        static_assert(dimension > 1);
        return values[1];
    }
    PointType y() const
    {
        static_assert(dimension > 1);
        return values[1];
    }

    PointType& z()
    {
        static_assert(dimension > 2);
        return values[2];
    }
    PointType z() const
    {
        static_assert(dimension > 2);
        return values[2];
    }

    PointType& value(int i)
    {
        assert(i >= 0 && i < dimension);
        return values[i];
    }

    PointType value(int i) const
    {
        assert(i >= 0 && i < dimension);
        return values[i];
    }

    Point& operator+=(const Point& other)
    {
        assert(other.size() == size());
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](PointType v1, PointType v2) { return v1 + v2; });
        return *this;
    }

    Point& operator-=(const Point& other)
    {
        assert(other.size() == size());
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](PointType v1, PointType v2) { return v1 - v2; });
        return *this;
    }

    Point& operator*=(const PointType scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(),
                       [scalar](PointType v) { return v * scalar; });
        return *this;
    }

    Point& operator*=(const Point& other)
    {
        x() *= other.x();
        y() *= other.y();
        return *this;
    }

    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator-(const Point& other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator-() const { return Point { -x(), -y(), -z() }; }

    Point operator*(const PointType scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator*(const Point& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    bool operator!=(const Point& other)
    {

        return std::all_of(values.begin(), values.end(),
                           [&other](PointType v1, PointType v2) { return v1 != v2; });
    }

    PointType length() const
    {
        return std::sqrt(std::accumulate(values.begin(), values.end(), 0.0,
                                         [](PointType v1, PointType v2) { return v1 + v2 * v2; }));
    }

    PointType distance_to(const Point& other) const { return (*this - other).length(); }

    Point& normalize(const PointType target_len = 1.0f)
    {
        const PointType current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point& cap_length(const PointType max_len)
    {
        assert(max_len > 0);

        const PointType current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }
};