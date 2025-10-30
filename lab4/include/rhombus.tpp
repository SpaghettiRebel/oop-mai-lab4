#pragma once
#include <cmath>
#include <stdexcept>

template <Scalar T>
Rhombus<T>::Rhombus(PointT left, PointT top, PointT right, PointT bottom) {
  pts.clear();
  pts.push_back(std::make_unique<PointT>(left));
  pts.push_back(std::make_unique<PointT>(top));
  pts.push_back(std::make_unique<PointT>(right));
  pts.push_back(std::make_unique<PointT>(bottom));

  if (!isValidRhombus())
    throw std::invalid_argument("Введены неправильные координаты");
}

template <Scalar T> Rhombus<T>::Rhombus(const Rhombus &other) {
  pts.clear();
  for (const auto &p : other.pts)
    pts.push_back(std::make_unique<PointT>(*p));
}

template <Scalar T> Rhombus<T> &Rhombus<T>::operator=(const Rhombus &other) {
  if (this == &other)
    return *this;
  pts.clear();
  for (const auto &p : other.pts)
    pts.push_back(std::make_unique<PointT>(*p));
  return *this;
}

template <Scalar T> std::unique_ptr<Figure<T>> Rhombus<T>::clone() const {
  return std::make_unique<Rhombus<T>>(*this);
}

template <Scalar T> typename Rhombus<T>::PointT Rhombus<T>::center() const {
  T sx{};
  T sy{};
  for (auto &p : pts) {
    sx += p->x;
    sy += p->y;
  }
  return PointT{sx / T(pts.size()), sy / T(pts.size())};
}

template <Scalar T> double Rhombus<T>::area() const {
  if (pts.size() != 4)
    return 0.0;
  double d1 = distance(*pts[0], *pts[2]); // горизонтальная диагональ
  double d2 = distance(*pts[1], *pts[3]); // вертикальная диагональ
  return 0.5 * d1 * d2;
}

template <Scalar T> void Rhombus<T>::print(std::ostream &os) const {
  os << "Rhombus ";
  for (const auto &p : pts)
    os << *p << " ";
  os << "area=" << area();
}

template <Scalar T> void Rhombus<T>::read(std::istream &is) {
  std::vector<PointT> temp_pts(4);
  for (int i = 0; i < 4; ++i)
    is >> temp_pts[i].x >> temp_pts[i].y;

  // Найти центр
  T cx{}, cy{};
  for (const auto &pt : temp_pts) {
    cx += pt.x;
    cy += pt.y;
  }
  cx /= T(4);
  cy /= T(4);

  pts.clear();
  pts.resize(4);

  for (const auto &pt : temp_pts) {
    T dx = pt.x - cx;
    T dy = pt.y - cy;

    if (std::abs(double(dx)) > std::abs(double(dy))) {
      // ближе к горизонтальной оси
      if (dx < T(0))
        pts[0] = std::make_unique<PointT>(pt); // left
      else
        pts[2] = std::make_unique<PointT>(pt); // right
    } else {
      // ближе к вертикальной оси
      if (dy > T(0))
        pts[1] = std::make_unique<PointT>(pt); // top
      else
        pts[3] = std::make_unique<PointT>(pt); // bottom
    }
  }

  if (!isValidRhombus())
    throw std::invalid_argument("Введены неправильные координаты");
}

template <Scalar T>
double Rhombus<T>::distance(const PointT &a, const PointT &b) const {
  return std::hypot(double(a.x - b.x), double(a.y - b.y));
}

template <Scalar T> bool Rhombus<T>::isValidRhombus() const {
  if (pts.size() != 4)
    return false;

  double s1 = distance(*pts[0], *pts[1]); // left-top
  double s2 = distance(*pts[1], *pts[2]); // top-right
  double s3 = distance(*pts[2], *pts[3]); // right-bottom
  double s4 = distance(*pts[3], *pts[0]); // bottom-left

  bool equalSides = std::abs(s1 - s2) < 1e-8 && std::abs(s2 - s3) < 1e-8 &&
                    std::abs(s3 - s4) < 1e-8;

  PointT d1{pts[2]->x - pts[0]->x, pts[2]->y - pts[0]->y};
  PointT d2{pts[1]->x - pts[3]->x, pts[1]->y - pts[3]->y};
  bool perpendicular = std::abs(double(d1.x * d2.x + d1.y * d2.y)) < 1e-8;

  return equalSides && perpendicular;
}
