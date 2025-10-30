#pragma once
#include "figure.hpp"
#include <memory>
#include <vector>

template <Scalar T> class Rhombus : public Figure<T> {
public:
  using PointT = Point<T>;

  Rhombus() = default;
  Rhombus(PointT left, PointT top, PointT right, PointT bottom);

  Rhombus(const Rhombus &other);
  Rhombus &operator=(const Rhombus &other);

  std::unique_ptr<Figure<T>> clone() const override;
  PointT center() const override;
  double area() const override;
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;

private:
  std::vector<std::unique_ptr<PointT>> pts;
  bool isValidRhombus() const;
  double distance(const PointT &a, const PointT &b) const;
};

#include "rhombus.tpp"