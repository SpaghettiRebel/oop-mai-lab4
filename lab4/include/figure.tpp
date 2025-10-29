#pragma once
#include "figure.hpp"
#include <cmath>
#include <iostream>

template <Scalar T>
inline bool close_d(const double a, const double b, const double eps = 1e-6) {
  return std::fabs(a - b) < eps;
}

template <Scalar T>
inline bool close_pt(const Point<T> &A, const Point<T> &B,
                     const double eps = 1e-6) {
  return close_d<T>(double(A.x), double(B.x), eps) &&
         close_d<T>(double(A.y), double(B.y), eps);
}

// Потоковый ввод: делегирует конкретным фигурам через read()
template <Scalar T>
inline std::istream &operator>>(std::istream &is, Figure<T> &f) {
  f.read(is);
  return is;
}

// Свободная operator==: сравнение площади и геометрического центра
template <Scalar T>
inline bool operator==(const Figure<T> &a, const Figure<T> &b) {
  if (!close_d<T>(a.area(), b.area()))
    return false;
  Point<T> ca = a.center();
  Point<T> cb = b.center();
  return close_pt<T>(ca, cb);
}
