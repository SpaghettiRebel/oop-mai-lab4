#pragma once
#include <cassert>
#include <concepts>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>

template <class T>
concept Arrayable =
    std::is_default_constructible_v<T> && std::is_copy_constructible_v<T>;

template <Arrayable T> class Array {
public:
  Array();
  Array(const std::initializer_list<T> &il);
  Array(const Array &other);
  Array(Array &&other) noexcept;
  Array &operator=(const Array &other);
  Array &operator=(Array &&other) noexcept;
  ~Array() = default;

  void push_back(const T &v);
  void push_back(T &&v);
  template <typename... Args> void emplace_back(Args &&...args);

  void remove_at(size_t idx);
  size_t size() const noexcept { return _size; }
  size_t capacity() const noexcept { return _cap; }

  T &operator[](size_t idx);
  const T &operator[](size_t idx) const;

private:
  void grow_to(size_t newcap);

  size_t _size;
  size_t _cap;
  std::shared_ptr<T[]> _data;
};

#include "array.tpp"
