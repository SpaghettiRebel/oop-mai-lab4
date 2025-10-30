#pragma once

template <Scalar T> Trapezoid<T>::Trapezoid(T cx, T cy, T topA, T botB, T h) {
  set_by_center(cx, cy, topA, botB, h);
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
  double a = pts[0]->distTo(*pts[1]);
  double b = pts[2]->distTo(*pts[3]);
  double h = std::fabs(double(pts[0]->y) - double(pts[3]->y));
  return 0.5 * (a + b) * h;
}

template <Scalar T> void Trapezoid<T>::print(std::ostream &os) const {
  os << "Trapezoid ";
  for (const auto &p : pts)
    os << *p << " ";
  os << "area=" << area();
}

template <Scalar T> void Trapezoid<T>::read(std::istream &is) {
  T cx, cy, a, b, h;
  is >> cx >> cy >> a >> b >> h;
  set_by_center(cx, cy, a, b, h);
}

template <Scalar T>
void Trapezoid<T>::set_by_center(T cx, T cy, T a, T b, T h) {
  pts.clear();
  T hh = h / T(2);
  T halfA = a / T(2), halfB = b / T(2);
  pts.push_back(std::make_unique<PointT>(cx - halfA, cy + hh));
  pts.push_back(std::make_unique<PointT>(cx + halfA, cy + hh));
  pts.push_back(std::make_unique<PointT>(cx + halfB, cy - hh));
  pts.push_back(std::make_unique<PointT>(cx - halfB, cy - hh));
}
