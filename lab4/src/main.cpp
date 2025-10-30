#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

#include "array.hpp"
#include "rectangle.hpp"
#include "rhombus.hpp"
#include "trapezoid.hpp"

int main() {
  using T = double;

  Array<Rectangle<T>> arr_rects;
  arr_rects.emplace_back(T(0), T(0), T(2), T(1));
  arr_rects.emplace_back(T(1), T(1), T(3), T(2));

  std::cout << "Array<Rectangle<T>> (по значению):\n";
  for (size_t i = 0; i < arr_rects.size(); ++i) {
    std::cout << i << ": ";
    arr_rects[i].print(std::cout);
    std::cout << "\n";
  }

  Array<std::shared_ptr<Figure<T>>> arr;

  std::cout << "Введите номер действия:\n"
            << "  1: добавить прямоугольник\n"
            << "  2: добавить трапецию\n"
            << "  3: добавить ромб\n"
            << "  p: печать всех фигур\n"
            << "  s: суммарная площадь\n"
            << "  d: удалить фигуру\n"
            << "  0: выход\n";

  while (true) {
    std::cout << "Ввод: ";
    std::string cmd;
    if (!(std::cin >> cmd))
      break;
    try {
      if (cmd == "1") {
        std::cout << "Введите cx cy длина ширина: ";
        T cx, cy, w, h;
        std::cin >> cx >> cy >> w >> h;
        arr.push_back(std::make_shared<Rectangle<T>>(cx, cy, w, h));

      } else if (cmd == "2") {
        std::cout
            << "Введите cx cy верхнее_основание нижнее_основание height: ";
        T cx, cy, a, b, h;
        std::cin >> cx >> cy >> a >> b >> h;
        arr.push_back(std::make_shared<Trapezoid<T>>(cx, cy, a, b, h));

      } else if (cmd == "3") {
        std::cout << "Введите cx cy диагональ1 диагональ2: ";
        T cx, cy, d1, d2;
        std::cin >> cx >> cy >> d1 >> d2;
        arr.push_back(std::make_shared<Rhombus<T>>(cx, cy, d1, d2));

      } else if (cmd == "p") {
        for (size_t i = 0; i < arr.size(); ++i) {
          std::cout << i << ": " << *arr[i] << "\n";
        }

      } else if (cmd == "s") {
        double sum = 0.0;
        for (size_t i = 0; i < arr.size(); ++i)
          sum += static_cast<double>(*arr[i]);
        std::cout << "  Суммарная площадь = " << sum << "\n";

      } else if (cmd == "d") {
        std::cout << "Введите индекс удаляемой фигуры (начиная с 0): ";
        size_t idx;
        std::cin >> idx;
        if (idx >= arr.size())
          std::cout << "  Ошибка: неправильный индекс\n";
        else {
          arr.remove_at(idx);
        }

      } else if (cmd == "0") {
        break;
      } else {
        std::cout << "Ошибка: такого варианта нет\n";
      }
    } catch (const std::exception &e) {
      std::cout << "Ошибка: " << e.what() << "\n";
      std::cin.clear();
      std::string skip;
      std::getline(std::cin, skip);
    }
  }
  return 0;
}
