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
  arr_rects.emplace_back(typename Rectangle<T>::PointT{-1, -0.5},
                         typename Rectangle<T>::PointT{-1, 0.5},
                         typename Rectangle<T>::PointT{1, -0.5},
                         typename Rectangle<T>::PointT{1, 0.5});
  arr_rects.emplace_back(typename Rectangle<T>::PointT{-0.5, -1},
                         typename Rectangle<T>::PointT{-0.5, 1},
                         typename Rectangle<T>::PointT{2, -1},
                         typename Rectangle<T>::PointT{2, 1});

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
        std::cout << "Введите 4 точки (x y для каждой): ";
        T x1, y1, x2, y2, x3, y3, x4, y4;
        std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        auto rect = std::make_shared<Rectangle<T>>();
        std::istringstream iss(std::to_string(x1) + " " + std::to_string(y1) +
                               " " + std::to_string(x2) + " " +
                               std::to_string(y2) + " " + std::to_string(x3) +
                               " " + std::to_string(y3) + " " +
                               std::to_string(x4) + " " + std::to_string(y4));
        rect->read(iss);
        arr.push_back(rect);

      } else if (cmd == "2") {
        std::cout << "Введите 4 точки (x y для каждой): ";
        T x1, y1, x2, y2, x3, y3, x4, y4;
        std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        auto trap = std::make_shared<Trapezoid<T>>();
        std::istringstream iss(std::to_string(x1) + " " + std::to_string(y1) +
                               " " + std::to_string(x2) + " " +
                               std::to_string(y2) + " " + std::to_string(x3) +
                               " " + std::to_string(y3) + " " +
                               std::to_string(x4) + " " + std::to_string(y4));
        trap->read(iss);
        arr.push_back(trap);

      } else if (cmd == "3") {
        std::cout << "Введите 4 точки (x y для каждой): ";
        T x1, y1, x2, y2, x3, y3, x4, y4;
        std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        auto rhomb = std::make_shared<Rhombus<T>>();
        std::istringstream iss(std::to_string(x1) + " " + std::to_string(y1) +
                               " " + std::to_string(x2) + " " +
                               std::to_string(y2) + " " + std::to_string(x3) +
                               " " + std::to_string(y3) + " " +
                               std::to_string(x4) + " " + std::to_string(y4));
        rhomb->read(iss);
        arr.push_back(rhomb);

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
