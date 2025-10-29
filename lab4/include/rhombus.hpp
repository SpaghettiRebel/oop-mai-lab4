#pragma once
#include "figure.hpp"
#include <memory>
#include <vector>

template <Scalar T> class Rhombus : public Figure<T> {
public:
  using PointT = Point<T>;
  Rhombus() = default;
  Rhombus(T cx, T cy, T d1, T d2);

  Rhombus(const Rhombus &other);
  Rhombus &operator=(const Rhombus &other);

  std::unique_ptr<Figure<T>> clone() const override;
  PointT center() const override;
  double area() const override;
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;

private:
  std::vector<std::unique_ptr<PointT>> pts; // 4 vertices
  void set_by_center(T cx, T cy, T d1, T d2);
};

#include "rhombus.tpp"
