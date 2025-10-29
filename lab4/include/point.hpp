#pragma once
#include <cmath>
#include <concepts>
#include <iostream>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T> struct Point {
  T x{};
  T y{};
  Point() = default;
  Point(T xx, T yy) : x(xx), y(yy) {}
  double distTo(const Point &o) const noexcept {
    double dx = double(x) - double(o.x);
    double dy = double(y) - double(o.y);
    return std::sqrt(dx * dx + dy * dy);
  }
};

template <Scalar T>
inline std::ostream &operator<<(std::ostream &os, const Point<T> &p) {
  os << "(" << p.x << "," << p.y << ")";
  return os;
}
