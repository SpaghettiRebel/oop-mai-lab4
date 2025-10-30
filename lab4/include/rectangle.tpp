#pragma once
#include <cmath>
#include <iomanip>
#include <stdexcept>

template <Scalar T>
Rectangle<T>::Rectangle(PointT ll, PointT lu, PointT rl, PointT ru) {
  pts.clear();
  pts.push_back(std::make_unique<PointT>(ll));
  pts.push_back(std::make_unique<PointT>(lu));
  pts.push_back(std::make_unique<PointT>(rl));
  pts.push_back(std::make_unique<PointT>(ru));

  if (!isValidRectangle())
    throw std::invalid_argument("Введены неправильные координаты");
}

template <Scalar T> Rectangle<T>::Rectangle(const Rectangle &other) {
  pts.clear();
  pts.reserve(other.pts.size());
  for (const auto &p : other.pts)
    pts.push_back(std::make_unique<PointT>(*p));
}

template <Scalar T>
Rectangle<T> &Rectangle<T>::operator=(const Rectangle &other) {
  if (this == &other)
    return *this;
  pts.clear();
  pts.reserve(other.pts.size());
  for (const auto &p : other.pts)
    pts.push_back(std::make_unique<PointT>(*p));
  return *this;
}

template <Scalar T> std::unique_ptr<Figure<T>> Rectangle<T>::clone() const {
  return std::make_unique<Rectangle<T>>(*this);
}

template <Scalar T> typename Rectangle<T>::PointT Rectangle<T>::center() const {
  T sx{};
  T sy{};
  for (auto &p : pts) {
    sx += p->x;
    sy += p->y;
  }
  return PointT{sx / T(pts.size()), sy / T(pts.size())};
}

template <Scalar T> double Rectangle<T>::area() const {
  if (pts.size() != 4)
    return 0.0;
  double w = distance(*pts[0], *pts[2]);
  double h = distance(*pts[0], *pts[1]);
  return w * h;
}

template <Scalar T> void Rectangle<T>::print(std::ostream &os) const {
  os << "Rectangle ";
  for (const auto &p : pts)
    os << *p << " ";
  os << "area=" << area();
}

template <Scalar T> void Rectangle<T>::read(std::istream &is) {
  std::vector<PointT> temp_pts(4);
  for (int i = 0; i < 4; ++i)
    is >> temp_pts[i].x >> temp_pts[i].y;

  T min_x = temp_pts[0].x, max_x = temp_pts[0].x;
  T min_y = temp_pts[0].y, max_y = temp_pts[0].y;
  for (const auto &pt : temp_pts) {
    if (pt.x < min_x)
      min_x = pt.x;
    if (pt.x > max_x)
      max_x = pt.x;
    if (pt.y < min_y)
      min_y = pt.y;
    if (pt.y > max_y)
      max_y = pt.y;
  }

  pts.clear();
  pts.resize(4);

  for (const auto &pt : temp_pts) {
    if (std::abs(double(pt.x - min_x)) < 1e-8 &&
        std::abs(double(pt.y - min_y)) < 1e-8)
      pts[0] = std::make_unique<PointT>(pt);
    else if (std::abs(double(pt.x - min_x)) < 1e-8 &&
             std::abs(double(pt.y - max_y)) < 1e-8)
      pts[1] = std::make_unique<PointT>(pt);
    else if (std::abs(double(pt.x - max_x)) < 1e-8 &&
             std::abs(double(pt.y - min_y)) < 1e-8)
      pts[2] = std::make_unique<PointT>(pt);
    else if (std::abs(double(pt.x - max_x)) < 1e-8 &&
             std::abs(double(pt.y - max_y)) < 1e-8)
      pts[3] = std::make_unique<PointT>(pt);
  }

  if (!isValidRectangle())
    throw std::invalid_argument("Введены неправильные координаты");
}

template <Scalar T>
double Rectangle<T>::distance(const PointT &a, const PointT &b) const {
  return std::hypot(double(a.x - b.x), double(a.y - b.y));
}

template <Scalar T> bool Rectangle<T>::isValidRectangle() const {
  if (pts.size() != 4)
    return false;

  PointT AB{pts[1]->x - pts[0]->x, pts[1]->y - pts[0]->y};
  PointT BC{pts[3]->x - pts[1]->x, pts[3]->y - pts[1]->y};
  PointT CD{pts[2]->x - pts[3]->x, pts[2]->y - pts[3]->y};
  PointT DA{pts[0]->x - pts[2]->x, pts[0]->y - pts[2]->y};

  auto dot = [](const PointT &a, const PointT &b) {
    return a.x * b.x + a.y * b.y;
  };

  bool angleA = std::abs(double(dot(AB, DA))) < 1e-8;
  bool angleB = std::abs(double(dot(BC, AB))) < 1e-8;
  bool angleC = std::abs(double(dot(CD, BC))) < 1e-8;
  bool angleD = std::abs(double(dot(DA, CD))) < 1e-8;

  double lenAB = distance(*pts[0], *pts[1]);
  double lenBC = distance(*pts[1], *pts[3]);
  double lenCD = distance(*pts[3], *pts[2]);
  double lenDA = distance(*pts[2], *pts[0]);

  bool sidesAB_CD = std::abs(lenAB - lenCD) < 1e-8;
  bool sidesBC_DA = std::abs(lenBC - lenDA) < 1e-8;

  return angleA && angleB && angleC && angleD && sidesAB_CD && sidesBC_DA;
}
