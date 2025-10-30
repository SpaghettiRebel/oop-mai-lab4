#pragma once
#include <cmath>
#include <stdexcept>

template <Scalar T>
Trapezoid<T>::Trapezoid(PointT tl, PointT tr, PointT br, PointT bl) {
  pts.clear();
  pts.push_back(std::make_unique<PointT>(tl));
  pts.push_back(std::make_unique<PointT>(tr));
  pts.push_back(std::make_unique<PointT>(br));
  pts.push_back(std::make_unique<PointT>(bl));

  if (!isValidTrapezoid())
    throw std::invalid_argument("Введены неправильные координаты");
}

template <Scalar T> Trapezoid<T>::Trapezoid(const Trapezoid &other) {
  pts.clear();
  for (const auto &p : other.pts)
    pts.push_back(std::make_unique<PointT>(*p));
}

template <Scalar T>
Trapezoid<T> &Trapezoid<T>::operator=(const Trapezoid &other) {
  if (this == &other)
    return *this;
  pts.clear();
  for (const auto &p : other.pts)
    pts.push_back(std::make_unique<PointT>(*p));
  return *this;
}

template <Scalar T> std::unique_ptr<Figure<T>> Trapezoid<T>::clone() const {
  return std::make_unique<Trapezoid<T>>(*this);
}

template <Scalar T> typename Trapezoid<T>::PointT Trapezoid<T>::center() const {
  T sx{};
  T sy{};
  for (auto &p : pts) {
    sx += p->x;
    sy += p->y;
  }
  return PointT{sx / T(pts.size()), sy / T(pts.size())};
}

template <Scalar T> double Trapezoid<T>::area() const {
  if (pts.size() != 4)
    return 0.0;
  // pts[0]=tl, pts[1]=tr, pts[2]=br, pts[3]=bl
  double a = distance(*pts[0], *pts[1]); // верхнее основание
  double b = distance(*pts[3], *pts[2]); // нижнее основание
  double h = std::abs(double(pts[0]->y) - double(pts[3]->y)); // высота
  return 0.5 * (a + b) * h;
}

template <Scalar T> void Trapezoid<T>::print(std::ostream &os) const {
  os << "Trapezoid ";
  for (const auto &p : pts)
    os << *p << " ";
  os << "area=" << area();
}

template <Scalar T> void Trapezoid<T>::read(std::istream &is) {
  std::vector<PointT> temp_pts(4);
  for (int i = 0; i < 4; ++i)
    is >> temp_pts[i].x >> temp_pts[i].y;

  // Найти min и max по y
  T min_y = temp_pts[0].y, max_y = temp_pts[0].y;
  for (const auto &pt : temp_pts) {
    if (pt.y < min_y)
      min_y = pt.y;
    if (pt.y > max_y)
      max_y = pt.y;
  }

  pts.clear();
  pts.resize(4);

  // Разделить точки на верхние и нижние
  std::vector<PointT> top_pts, bottom_pts;
  for (const auto &pt : temp_pts) {
    if (std::abs(double(pt.y - max_y)) < 1e-8)
      top_pts.push_back(pt);
    else if (std::abs(double(pt.y - min_y)) < 1e-8)
      bottom_pts.push_back(pt);
  }

  // Сортировать по x для определения left и right
  if (top_pts.size() == 2) {
    if (top_pts[0].x < top_pts[1].x) {
      pts[0] = std::make_unique<PointT>(top_pts[0]); // tl
      pts[1] = std::make_unique<PointT>(top_pts[1]); // tr
    } else {
      pts[0] = std::make_unique<PointT>(top_pts[1]); // tl
      pts[1] = std::make_unique<PointT>(top_pts[0]); // tr
    }
  }

  if (bottom_pts.size() == 2) {
    if (bottom_pts[0].x < bottom_pts[1].x) {
      pts[3] = std::make_unique<PointT>(bottom_pts[0]); // bl
      pts[2] = std::make_unique<PointT>(bottom_pts[1]); // br
    } else {
      pts[3] = std::make_unique<PointT>(bottom_pts[1]); // bl
      pts[2] = std::make_unique<PointT>(bottom_pts[0]); // br
    }
  }

  if (!isValidTrapezoid())
    throw std::invalid_argument("Введены неправильные координаты");
}

template <Scalar T>
double Trapezoid<T>::distance(const PointT &a, const PointT &b) const {
  return std::hypot(double(a.x - b.x), double(a.y - b.y));
}

template <Scalar T> bool Trapezoid<T>::isValidTrapezoid() const {
  if (pts.size() != 4)
    return false;

  // Проверка что верхнее и нижнее основания параллельны (одинаковые y)
  bool topParallel = std::abs(double(pts[0]->y - pts[1]->y)) < 1e-8;
  bool bottomParallel = std::abs(double(pts[2]->y - pts[3]->y)) < 1e-8;

  // Проверка что есть высота
  bool hasHeight = std::abs(double(pts[0]->y - pts[3]->y)) > 1e-8;

  return topParallel && bottomParallel && hasHeight;
}
