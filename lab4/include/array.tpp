#pragma once

template <Arrayable T> Array<T>::Array() : _size(0), _cap(0), _data(nullptr) {}

template <Arrayable T> Array<T>::Array(const std::initializer_list<T> &il) {
  _size = il.size();
  _cap = _size ? _size : 1;
  _data = std::shared_ptr<T[]>(new T[_cap]);
  size_t i = 0;
  for (const auto &e : il)
    _data[i++] = e;
}

template <Arrayable T> Array<T>::Array(const Array &other) {
  _size = other._size;
  _cap = other._cap;
  if (_cap) {
    _data = std::shared_ptr<T[]>(new T[_cap]);
    for (size_t i = 0; i < _size; ++i)
      _data[i] = other._data[i];
  } else {
    _data = nullptr;
  }
}

template <Arrayable T> Array<T>::Array(Array &&other) noexcept {
  _size = other._size;
  _cap = other._cap;
  _data = other._data;
  other._size = 0;
  other._cap = 0;
  other._data = nullptr;
}

template <Arrayable T> Array<T> &Array<T>::operator=(const Array &other) {
  if (this == &other)
    return *this;
  _size = other._size;
  _cap = other._cap;
  if (_cap) {
    _data = std::shared_ptr<T[]>(new T[_cap]);
    for (size_t i = 0; i < _size; ++i)
      _data[i] = other._data[i];
  } else
    _data = nullptr;
  return *this;
}

template <Arrayable T> Array<T> &Array<T>::operator=(Array &&other) noexcept {
  if (this == &other)
    return *this;
  _size = other._size;
  _cap = other._cap;
  _data = other._data;
  other._size = 0;
  other._cap = 0;
  other._data = nullptr;
  return *this;
}

template <Arrayable T> void Array<T>::grow_to(size_t newcap) {
  if (newcap <= _cap)
    return;
  std::shared_ptr<T[]> newdata(new T[newcap]);
  for (size_t i = 0; i < _size; ++i)
    newdata[i] = std::move(_data[i]);
  _data = std::move(newdata);
  _cap = newcap;
}

template <Arrayable T> void Array<T>::push_back(const T &v) {
  if (_size >= _cap)
    grow_to(_cap ? _cap * 2 : 4);
  _data[_size++] = v;
}

template <Arrayable T> void Array<T>::push_back(T &&v) {
  if (_size >= _cap)
    grow_to(_cap ? _cap * 2 : 4);
  _data[_size++] = std::move(v);
}

template <Arrayable T>
template <typename... Args>
void Array<T>::emplace_back(Args &&...args) {
  if (_size >= _cap)
    grow_to(_cap ? _cap * 2 : 4);
  _data[_size++] = T(std::forward<Args>(args)...);
}

template <Arrayable T> void Array<T>::remove_at(size_t idx) {
  if (idx >= _size)
    throw std::out_of_range("remove_at: index out of range");
  for (size_t i = idx; i + 1 < _size; ++i)
    _data[i] = std::move(_data[i + 1]);
  --_size;
}

template <Arrayable T> T &Array<T>::operator[](size_t idx) {
  assert(idx < _size);
  return _data[idx];
}

template <Arrayable T> const T &Array<T>::operator[](size_t idx) const {
  assert(idx < _size);
  return _data[idx];
}
