// tests/test_figures.cpp
#include "figure.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "rhombus.hpp"
#include "trapezoid.hpp"

#include <gtest/gtest.h>
#include <iomanip>
#include <memory>
#include <sstream>
#include <vector>

static constexpr double EPS = 1e-6;

static bool output_contains_area(const std::string &out, double area) {
  std::ostringstream tmp;
  tmp << std::fixed << std::setprecision(6) << area;
  // сравниваем по подстроке (в выводе area печатается с плавающей точкой)
  return out.find(tmp.str()) != std::string::npos;
}

TEST(RectangleTest, AreaAndCenter) {
  Rectangle<double> r(1.5, -2.0, 4.0,
                      4.0); // center x=1.5,y=-2.0, width=4 height=4
  EXPECT_NEAR(r.area(), 16.0, EPS);
  auto c = r.center();
  EXPECT_NEAR(c.x, 1.5, EPS);
  EXPECT_NEAR(c.y, -2.0, EPS);
}

TEST(RectangleTest, IOAndClone) {
  // формат read: cx cy width height
  std::istringstream in("0.0 1.0 3.5 2.0");
  Rectangle<double> r;
  EXPECT_NO_THROW(r.read(in));
  EXPECT_NEAR(r.area(), 3.5 * 2.0, EPS);

  std::ostringstream out;
  out << r;
  std::string o = out.str();
  EXPECT_FALSE(o.empty());
  EXPECT_TRUE(output_contains_area(o, r.area()));

  // clone (unique_ptr)
  auto copy = r.clone();
  auto rc = dynamic_cast<Rectangle<double> *>(copy.get());
  ASSERT_NE(rc, nullptr);
  EXPECT_NEAR(rc->area(), r.area(), EPS);
}

TEST(TrapezoidTest, AreaAndCenter) {
  // center 0,0; top a=2, bottom b=4, height=1 -> area = (2+4)/2 *1 = 3
  Trapezoid<double> t(0.0, 0.0, 2.0, 4.0, 1.0);
  EXPECT_NEAR(t.area(), 3.0, EPS);
  auto c = t.center();
  EXPECT_NEAR(c.x, 0.0, EPS);
  EXPECT_NEAR(c.y, 0.0, EPS);

  std::ostringstream out;
  out << t;
  std::string o = out.str();
  EXPECT_FALSE(o.empty());
  EXPECT_TRUE(output_contains_area(o, t.area()));
}

TEST(RhombusTest, AreaAndIOClone) {
  // diagonals d1=2, d2=2 => area = d1*d2/2 = 2
  Rhombus<double> r(1.0, 2.0, 2.0, 2.0);
  EXPECT_NEAR(r.area(), 2.0, EPS);
  auto c = r.center();
  EXPECT_NEAR(c.x, 1.0, EPS);
  EXPECT_NEAR(c.y, 2.0, EPS);

  std::ostringstream out;
  out << r;
  EXPECT_TRUE(output_contains_area(out.str(), r.area()));

  auto copy = r.clone();
  auto rc = dynamic_cast<Rhombus<double> *>(copy.get());
  ASSERT_NE(rc, nullptr);
  EXPECT_NEAR(rc->area(), r.area(), EPS);
}

TEST(PolymorphicEqualityAndSumArea, EqualAndSum) {
  Rectangle<double> a(0, 0, 2.0, 2.0); // area 4
  Rectangle<double> b(0, 0, 2.0, 2.0); // area 4
  EXPECT_TRUE(a == b);

  std::vector<std::unique_ptr<Figure<double>>> arr;
  arr.push_back(std::make_unique<Rectangle<double>>(0.0, 0.0, 2.0, 2.0)); // 4
  arr.push_back(std::make_unique<Rectangle<double>>(0.0, 0.0, 3.0, 2.0)); // 6
  arr.push_back(std::make_unique<Rhombus<double>>(0.0, 0.0, 2.0, 2.0));   // 2

  double sum = 0.0;
  for (auto &f : arr)
    sum += f->area();

  EXPECT_NEAR(sum, 4.0 + 6.0 + 2.0, 1e-6);
}

TEST(CloneThroughBasePointer, PolymorphicCopy) {
  Rhombus<double> r(5.0, 5.0, 1.5, 2.0);
  Figure<double> *base = &r;
  auto copy = base->clone();
  ASSERT_NE(copy, nullptr);
  auto rc = dynamic_cast<Rhombus<double> *>(copy.get());
  ASSERT_NE(rc, nullptr);
  EXPECT_NEAR(rc->area(), r.area(), EPS);
}
