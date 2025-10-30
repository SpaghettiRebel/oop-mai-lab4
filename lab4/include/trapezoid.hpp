#pragma once
#include "figure.hpp"
#include <memory>
#include <vector>

template <Scalar T> class Trapezoid : public Figure<T> {
public:
  using PointT = Point<T>;

  Trapezoid() = default;
  Trapezoid(PointT tl, PointT tr, PointT br, PointT bl);

  Trapezoid(const Trapezoid &other);
  Trapezoid &operator=(const Trapezoid &other);

  std::unique_ptr<Figure<T>> clone() const override;
  PointT center() const override;
  double area() const override;
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;

private:
  std::vector<std::unique_ptr<PointT>> pts; // tl, tr, br, bl
  bool isValidTrapezoid() const;
  double distance(const PointT &a, const PointT &b) const;
};

#include "trapezoid.tpp"
