#pragma once

template <Scalar T> Rhombus<T>::Rhombus(T cx, T cy, T d1, T d2) {
  set_by_center(cx, cy, d1, d2);
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
  double d1 = pts[0]->distTo(*pts[2]);
  double d2 = pts[1]->distTo(*pts[3]);
  return 0.5 * d1 * d2;
}

template <Scalar T> void Rhombus<T>::print(std::ostream &os) const {
  os << "Rhombus ";
  for (const auto &p : pts)
    os << *p << " ";
  os << "area=" << area();
}

template <Scalar T> void Rhombus<T>::read(std::istream &is) {
  T cx, cy, d1, d2;
  is >> cx >> cy >> d1 >> d2;
  set_by_center(cx, cy, d1, d2);
}

template <Scalar T> void Rhombus<T>::set_by_center(T cx, T cy, T d1, T d2) {
  pts.clear();
  T half1 = d1 / T(2), half2 = d2 / T(2);
  // left, top, right, bottom (so diagonals horizontal/vertical)
  pts.push_back(std::make_unique<PointT>(cx - half1, cy));
  pts.push_back(std::make_unique<PointT>(cx, cy + half2));
  pts.push_back(std::make_unique<PointT>(cx + half1, cy));
  pts.push_back(std::make_unique<PointT>(cx, cy - half2));
}
