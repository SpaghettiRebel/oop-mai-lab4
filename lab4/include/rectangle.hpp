#pragma once
#include "figure.hpp"
#include <memory>
#include <vector>

template <Scalar T> class Rectangle : public Figure<T> {
public:
  using PointT = Point<T>;

  Rectangle() = default;
  Rectangle(PointT ll, PointT lu, PointT rl, PointT ru);

  Rectangle(const Rectangle &other);
  Rectangle(Rectangle &&) noexcept = default;
  Rectangle &operator=(const Rectangle &other);
  Rectangle &operator=(Rectangle &&) noexcept = default;

  std::unique_ptr<Figure<T>> clone() const override;
  PointT center() const override;
  double area() const override;
  void print(std::ostream &os) const override;
  void read(std::istream &is) override;

private:
  std::vector<std::unique_ptr<PointT>> pts;
  bool isValidRectangle() const;
  double distance(const PointT &a, const PointT &b) const;
};

#include "rectangle.tpp"