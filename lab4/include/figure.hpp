#pragma once
#include "point.hpp"
#include <istream>
#include <memory>
#include <ostream>

template <Scalar T> class Figure {
public:
  using PointT = Point<T>;
  Figure() = default;
  virtual ~Figure() = default;

  virtual std::unique_ptr<Figure<T>> clone() const = 0;
  virtual PointT center() const = 0;
  virtual double area() const = 0;
  virtual void print(std::ostream &os) const = 0;
  virtual void read(std::istream &is) = 0;

  explicit operator double() const { return area(); }
};

template <Scalar T>
inline std::ostream &operator<<(std::ostream &os, const Figure<T> &f) {
  f.print(os);
  return os;
}

template <Scalar T> bool operator==(const Figure<T> &a, const Figure<T> &b);

#include "figure.tpp"
