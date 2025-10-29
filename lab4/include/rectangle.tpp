#pragma once
#include <iomanip>

template <Scalar T> Rectangle<T>::Rectangle(T cx, T cy, T width, T height) {
  set_by_center(cx, cy, width, height);
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
  double w = pts[0]->distTo(*pts[1]);
  double h = pts[1]->distTo(*pts[2]);
  return w * h;
}

template <Scalar T> void Rectangle<T>::print(std::ostream &os) const {
  os << "Rectangle ";
  for (const auto &p : pts)
    os << *p << " ";
  os << "area=" << area();
}

template <Scalar T> void Rectangle<T>::read(std::istream &is) {
  T cx, cy, w, h;
  is >> cx >> cy >> w >> h;
  set_by_center(cx, cy, w, h);
}

template <Scalar T> void Rectangle<T>::set_by_center(T cx, T cy, T w, T h) {
  pts.clear();
  T hw = w / T(2);
  T hh = h / T(2);
  pts.push_back(std::make_unique<PointT>(cx - hw, cy - hh)); // bl
  pts.push_back(std::make_unique<PointT>(cx + hw, cy - hh)); // br
  pts.push_back(std::make_unique<PointT>(cx + hw, cy + hh)); // tr
  pts.push_back(std::make_unique<PointT>(cx - hw, cy + hh)); // tl
}
